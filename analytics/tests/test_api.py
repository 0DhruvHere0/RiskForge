from datetime import date
import numpy as np
from fastapi.testclient import TestClient
from riskforge.api import create_app
from riskforge.data.models import HistoricalPriceSeries
from riskforge.data.portfolio_data import PortfolioDataService
from riskforge.portfolio_forecast import PortfolioForecaster
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
def test_health_endpoint():
    service=PortfolioAnalysisService(
        PortfolioDataService(FakeProvider()),
        PortfolioForecaster(fake_simulator)
    )
    client=TestClient(
        create_app(
            PortfolioDataService(FakeProvider()),
            service
        )
    )
    response=client.get("/health")
    assert response.status_code==200
    assert response.json()=={"status": "ok"}
def test_portfolio_forecast_endpoint():
    service=PortfolioAnalysisService(
        PortfolioDataService(FakeProvider()),
        PortfolioForecaster(fake_simulator)
    )
    client=TestClient(
        create_app(
            PortfolioDataService(FakeProvider()),
            service
        )
    )
    response=client.post(
        "/portfolio/forecast",
        json={
            "holdings": [
                {
                    "symbol": "AAA",
                    "quantity": 2.0,
                    "purchase_price": 95.0,
                    "current_price": 100.0,
                    "drift": 0.05,
                    "volatility": 0.20
                }
            ],
            "start": "2025-01-01",
            "end": "2025-01-02",
            "horizon": 10.0,
            "path_count": 4,
            "seed": 42
        }
    )
    assert response.status_code==200
    assert response.json()["expected_value"]==300.0