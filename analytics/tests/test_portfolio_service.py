import numpy as np
from riskforge.data.models import HistoricalPriceSeries
from dataclasses import dataclass
from datetime import date
from riskforge.data.portfolio_data import PortfolioDataService
from riskforge.data.portfolio_data import PortfolioHolding
from riskforge.portfolio_forecast import ForecastHolding
from riskforge.portfolio_forecast import PortfolioForecast
from riskforge.portfolio_forecast import PortfolioForecaster
from riskforge.portfolio_forecast_analysis import PortfolioForecastSummary
from riskforge.portfolio_forecast_analysis import summarize_portfolio_forecast
from riskforge.data.portfolio_workflow import PortfolioDataset
from riskforge.data.portfolio_workflow import PortfolioWorkflow
from riskforge.portfolio_service import PortfolioAnalysisService
class FakeProvider:
    def history(
        self,
        symbol: str,
        start: date,
        end: date
    ):
        return HistoricalPriceSeries(
            symbol=symbol,
            dates=["2025-01-01", "2025-01-02"],
            closes=np.asarray([100.0, 101.0])
        )
def fake_simulator(
    initial_price: float,
    drift: float,
    volatility: float,
    time: float,
    path_count: int,
    seed: int
):
    return np.full(
        path_count,
        initial_price*(1.0+drift*time)
    )
def test_analyzes_portfolio_data_and_forecast():
    service=PortfolioAnalysisService(
        PortfolioDataService(FakeProvider()),
        PortfolioForecaster(fake_simulator)
    )
    holdings=[
        PortfolioHolding(
            symbol="AAA",
            quantity=2.0,
            purchase_price=95.0
        )
    ]
    forecast_holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        )
    ]
    result=service.analyze(
        holdings,
        forecast_holdings,
        {"AAA": 2.0},
        date(2025, 1, 1),
        date(2025, 1, 2),
        10.0,
        4,
        42
    )
    assert result.dataset.dates==[
        "2025-01-01",
        "2025-01-02"
    ]
    np.testing.assert_allclose(
        result.forecast.prices["AAA"],
        np.full(4, 150.0)
    )
    assert result.summary.expected_value==300.0