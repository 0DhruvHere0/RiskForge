import numpy as np
import pytest
from riskforge.portfolio_forecast import ForecastHolding
from riskforge.portfolio_forecast import PortfolioForecaster
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
def test_forecasts_prices_for_each_holding():
    forecaster=PortfolioForecaster(fake_simulator)
    result=forecaster.forecast(
        [
            ForecastHolding(
                symbol="AAA",
                current_price=100.0,
                drift=0.05,
                volatility=0.20
            ),
            ForecastHolding(
                symbol="BBB",
                current_price=200.0,
                drift=0.03,
                volatility=0.15
            )
        ],
        10.0,
        4,
        42
    )
    np.testing.assert_allclose(
        result.prices["AAA"],
        np.full(4, 150.0)
    )
    np.testing.assert_allclose(
        result.prices["BBB"],
        np.full(4, 260.0)
    )
def test_rejects_empty_holdings():
    forecaster=PortfolioForecaster(fake_simulator)
    with pytest.raises(ValueError):
        forecaster.forecast([], 10.0, 4, 42)
def test_rejects_invalid_time():
    forecaster=PortfolioForecaster(fake_simulator)
    holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        )
    ]
    with pytest.raises(ValueError):
        forecaster.forecast(holdings, 0.0, 4, 42)
def test_rejects_invalid_path_count():
    forecaster=PortfolioForecaster(fake_simulator)
    holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        )
    ]
    with pytest.raises(ValueError):
        forecaster.forecast(holdings, 10.0, 0, 42)