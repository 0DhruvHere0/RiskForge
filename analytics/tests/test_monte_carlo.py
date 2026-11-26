import numpy as np
from riskforge import simulate_gbm_terminal_prices
def test_gbm_terminal_price_count():
    prices=simulate_gbm_terminal_prices(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42
    )
    assert isinstance(prices, np.ndarray)
    assert prices.shape==(1000,)
    assert np.all(np.isfinite(prices))
    assert np.all(prices>0.0)
def test_gbm_terminal_prices_are_deterministic():
    first=simulate_gbm_terminal_prices(
        100.0,
        0.05,
        0.20,
        1.0,
        100,
        42
    )
    second=simulate_gbm_terminal_prices(
        100.0,
        0.05,
        0.20,
        1.0,
        100,
        42
    )
    np.testing.assert_array_equal(first, second)