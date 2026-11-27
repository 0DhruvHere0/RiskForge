from fastapi.testclient import TestClient
from riskforge.api import create_app
from riskforge.data.instruments import Instrument
from riskforge.data.portfolio_data import PortfolioDataService
class FakeProvider:
    def search(self, query: str):
        return [
            Instrument(
                symbol="AAA",
                name="Alpha Asset",
                instrument_type="stock",
                exchange="TEST",
                currency="USD"
            )
        ]
def test_search_requires_api_key_in_production(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ENV",
        "production"
    )
    monkeypatch.setenv(
        "RISKFORGE_API_KEY",
        "test-secret"
    )
    client=TestClient(
        create_app(
            PortfolioDataService(FakeProvider()),
            None
        )
    )
    response=client.get(
        "/instruments/search",
        params={"query": "alpha"}
    )
    assert response.status_code==401
def test_search_accepts_valid_api_key(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ENV",
        "production"
    )
    monkeypatch.setenv(
        "RISKFORGE_API_KEY",
        "test-secret"
    )
    client=TestClient(
        create_app(
            PortfolioDataService(FakeProvider()),
            None
        )
    )
    response=client.get(
        "/instruments/search",
        params={"query": "alpha"},
        headers={"X-API-Key": "test-secret"}
    )
    assert response.status_code==200
    assert response.json()[0]["symbol"]=="AAA"
def test_health_remains_public(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ENV",
        "production"
    )
    monkeypatch.setenv(
        "RISKFORGE_API_KEY",
        "test-secret"
    )
    client=TestClient(
        create_app(
            PortfolioDataService(FakeProvider()),
            None
        )
    )
    response=client.get("/health")
    assert response.status_code==200