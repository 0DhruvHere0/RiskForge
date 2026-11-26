from datetime import date
import pytest
from riskforge.data.holdings import Holding
from riskforge.data.instruments import Instrument
from riskforge.data.portfolio_input import PortfolioRequest
from riskforge.data.portfolio_validation import validate_portfolio_request
def create_holding():
    return Holding(
        Instrument(
            "TEST",
            "Test Stock",
            "stock",
            "NSE",
            "INR"
        ),
        100.0,
        10.0,
        date(2025, 1, 1)
    )
def test_validates_portfolio_request():
    request=PortfolioRequest(
        [create_holding()],
        10.0,
        0.95
    )
    assert validate_portfolio_request(request)==request
def test_rejects_empty_portfolio():
    request=PortfolioRequest([], 10.0, 0.95)
    with pytest.raises(ValueError):
        validate_portfolio_request(request)
def test_rejects_invalid_holding_period():
    request=PortfolioRequest(
        [create_holding()],
        0.0,
        0.95
    )
    with pytest.raises(ValueError):
        validate_portfolio_request(request)