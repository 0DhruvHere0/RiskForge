from fastapi.testclient import TestClient
from riskforge.api import create_app
from riskforge.data.portfolio_data import PortfolioDataService
from riskforge.observability import configure_logging
def test_configure_logging_does_not_fail():
    configure_logging()
def test_request_id_is_returned():
    client=TestClient(
        create_app(
            PortfolioDataService(None),
            None
        )
    )
    response=client.get(
        "/health",
        headers={"X-Request-ID": "test-request"}
    )
    assert response.status_code==200
    assert response.headers["X-Request-ID"]=="test-request"