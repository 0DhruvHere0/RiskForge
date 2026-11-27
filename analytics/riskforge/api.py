from datetime import date
from fastapi import FastAPI
from pydantic import BaseModel
from .data.portfolio_data import PortfolioDataService
from .data.portfolio_data import PortfolioHolding
from .portfolio_forecast import ForecastHolding
from .portfolio_service import PortfolioAnalysisService
class HoldingRequest(BaseModel):
    symbol: str
    quantity: float
    purchase_price: float
    current_price: float
    drift: float
    volatility: float
class PortfolioForecastRequest(BaseModel):
    holdings: list[HoldingRequest]
    start: date
    end: date
    horizon: float
    path_count: int
    seed: int
class PortfolioForecastResponse(BaseModel):
    expected_value: float
    lower_value: float
    median_value: float
    upper_value: float
def create_app(
    data_service: PortfolioDataService,
    analysis_service: PortfolioAnalysisService
):
    app=FastAPI(
        title="RiskForge Analytics",
        version="0.1.0"
    )
    @app.get("/health")
    def health():
        return {"status": "ok"}
    @app.post(
        "/portfolio/forecast",
        response_model=PortfolioForecastResponse
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