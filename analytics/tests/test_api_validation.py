from datetime import date
import pytest
from riskforge.api import HoldingRequest
from riskforge.api import PortfolioForecastRequest
def valid_holding():
    return HoldingRequest(
        symbol="AAA",
        quantity=1.0,
        purchase_price=100.0,
        current_price=110.0,
        drift=0.05,
        volatility=0.20
    )
def test_rejects_non_positive_quantity():
    with pytest.raises(ValueError):
        HoldingRequest(
            symbol="AAA",
            quantity=0.0,
            purchase_price=100.0,
            current_price=110.0,
            drift=0.05,
            volatility=0.20
        )
def test_rejects_negative_volatility():
    with pytest.raises(ValueError):
        HoldingRequest(
            symbol="AAA",
            quantity=1.0,
            purchase_price=100.0,
            current_price=110.0,
            drift=0.05,
            volatility=-0.20
        )
def test_rejects_reversed_dates():
    with pytest.raises(ValueError):
        PortfolioForecastRequest(
            holdings=[valid_holding()],
            start=date(2026, 1, 2),
            end=date(2026, 1, 1),
            horizon=10.0,
            path_count=100,
            seed=42
        )
def test_accepts_valid_request():
    request=PortfolioForecastRequest(
        holdings=[valid_holding()],
        start=date(2026, 1, 1),
        end=date(2026, 1, 2),
        horizon=10.0,
        path_count=100,
        seed=42
    )
    assert request.path_count==100