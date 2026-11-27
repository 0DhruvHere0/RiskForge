from fastapi.testclient import TestClient
from riskforge.api_errors import runtime_error_handler
from riskforge.api_errors import value_error_handler
def test_value_error_handler_returns_bad_request():
    response=value_error_handler(
        None,
        ValueError("invalid value")
    )
    assert response.status_code==400
def test_runtime_error_handler_hides_upstream_details():
    response=runtime_error_handler(
        None,
        RuntimeError("private provider failure")
    )
    assert response.status_code==502