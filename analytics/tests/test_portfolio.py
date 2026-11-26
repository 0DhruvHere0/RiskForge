import numpy as np
from riskforge import calculate_portfolio_losses
from riskforge import estimate_portfolio_risk
from riskforge import simulate_multi_asset_gbm_terminal_prices
def test_multi_asset_simulation_shape():
    prices=simulate_multi_asset_gbm_terminal_prices(
        [100.0, 200.0],
        [0.05, 0.03],
        [0.20, 0.15],
        [[1.0, 0.0], [0.0, 1.0]],
        1.0,
        100,
        42
    )
    assert isinstance(prices, np.ndarray)
    assert prices.shape==(100, 2)
    assert np.all(np.isfinite(prices))
    assert np.all(prices>0.0)
def test_portfolio_risk_pipeline():
    terminal_prices=np.array([
        [105.0, 205.0],
        [95.0, 190.0],
        [110.0, 210.0],
        [90.0, 180.0],
    ])
    initial_prices=[100.0, 200.0]
    weights=[0.5, 0.5]
    losses=calculate_portfolio_losses(
        terminal_prices,
        initial_prices,
        weights
    )
    result=estimate_portfolio_risk(
        terminal_prices,
        initial_prices,
        weights,
        0.75
    )
    assert losses.shape==(4,)
    assert set(result)=={
        "value_at_risk",
        "expected_shortfall",
    }