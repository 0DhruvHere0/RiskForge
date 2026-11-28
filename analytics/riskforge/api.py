import os
from datetime import date
from fastapi import Depends
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from .data.portfolio_data import PortfolioDataService
from .data.portfolio_data import PortfolioHolding
from .portfolio_forecast import ForecastHolding
from .portfolio_service import PortfolioAnalysisService
from .security import allowed_origins
from .security import require_api_key
from .api_errors import runtime_error_handler
from .api_errors import value_error_handler
from pydantic import BaseModel
from pydantic import Field
from pydantic import model_validator
from .observability import RequestIdMiddleware
from .observability import configure_logging
class HoldingRequest(BaseModel):
    symbol: str
    quantity: float= Field(gt=0.0)
    purchase_price: float= Field(gt= 0.0)
    current_price: float= Field(gt= 0.0)
    drift: float
    volatility: float= Field(gt =0.0)
class PortfolioForecastRequest(BaseModel):
    holdings: list[HoldingRequest]= Field(min_length=1)
    start: date
    end: date
    horizon: float= Field(gt= 0.0)
    path_count: int= Field(gt= 0.0)
    seed: int
    @model_validator(mode="after")
    def validate_dates(self):
        if self.start>self.end:
            raise ValueError("start must not be after end")
        return self
class PortfolioForecastResponse(BaseModel):
    expected_value: float
    lower_value: float
    median_value: float
    upper_value: float
def create_app(
    data_service: PortfolioDataService,
    analysis_service: PortfolioAnalysisService
):
    production=os.getenv(
        "RISKFORGE_ENV",
        "development"
    ).lower()=="production"
    app=FastAPI(
        title="RiskForge Analytics",
        version="0.1.0",
        docs_url=None if production else "/docs",
        redoc_url=None if production else "/redoc",
        openapi_url=None if production else "/openapi.json"
    )
    configure_logging()
    app.add_middleware(RequestIdMiddleware)
    app.add_exception_handler(
        ValueError,
        value_error_handler
    )
    app.add_exception_handler(
        RuntimeError,
        runtime_error_handler
    )
    app.add_middleware(
        CORSMiddleware,
        allow_origins=allowed_origins(),
        allow_credentials=True,
        allow_methods=["GET", "POST"],
        allow_headers=["*"]
    )
    @app.get("/health")
    def health():
        return {"status": "ok"}
    @app.get(
        "/instruments/search",
        dependencies=[Depends(require_api_key)]
    )
    def search_instruments(query: str):
        instruments=data_service.search(query)
        return [
            {
                "symbol": instrument.symbol,
                "name": instrument.name,
                "instrument_type": instrument.instrument_type.lower().replace(
                    " ", "_"
                ),
                "exchange": instrument.exchange,
                "currency": instrument.currency,
                "source": data_service.source_for(
                    instrument.symbol
                )
            }
            for instrument in instruments
        ]
    @app.post(
        "/portfolio/forecast",
        response_model=PortfolioForecastResponse,
        dependencies=[Depends(require_api_key)]
    )
    def portfolio_forecast(request: PortfolioForecastRequest):
        holdings=[
            PortfolioHolding(
                symbol=item.symbol,
                quantity=item.quantity,
                purchase_price=item.purchase_price
            )
            for item in request.holdings
        ]
        forecast_holdings=[
            ForecastHolding(
                symbol=item.symbol,
                current_price=item.current_price,
                drift=item.drift,
                volatility=item.volatility
            )
            for item in request.holdings
        ]
        quantities={
            item.symbol: item.quantity
            for item in request.holdings
        }
        result=analysis_service.analyze(
            holdings,
            forecast_holdings,
            quantities,
            request.start,
            request.end,
            request.horizon,
            request.path_count,
            request.seed
        )
        return PortfolioForecastResponse(
            expected_value=result.summary.expected_value,
            lower_value=result.summary.lower_value,
            median_value=result.summary.median_value,
            upper_value=result.summary.upper_value
        )
    return app