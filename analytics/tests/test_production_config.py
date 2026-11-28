from fastapi.testclient import TestClient
from riskforge.api import create_app
from riskforge.data.portfolio_data import PortfolioDataService
def test_development_exposes_documentation(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ENV",
        "development"
    )
    client=TestClient(
        create_app(
            PortfolioDataService(None),
            None
        )
    )
    response=client.get("/docs")
    assert response.status_code==200
def test_production_hides_documentation(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ENV",
        "production"
    )
    client=TestClient(
        create_app(
            PortfolioDataService(None),
            None
        )
    )
    assert client.get("/docs").status_code==404
    assert client.get("/redoc").status_code==404
    assert client.get("/openapi.json").status_code==404