from datetime import date
import numpy as np
from fastapi.testclient import TestClient
from riskforge.application import create_application
from riskforge.data.models import HistoricalPriceSeries
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
def test_create_application_builds_health_endpoint():
    client=TestClient(
        create_application(FakeProvider())
    )
    response=client.get("/health")
    assert response.status_code==200
    assert response.json()=={"status": "ok"}