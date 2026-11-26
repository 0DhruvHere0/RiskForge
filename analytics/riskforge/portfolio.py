import numpy as np
from ._native import calculate_portfolio_losses as _calculate_portfolio_losses
from ._native import estimate_portfolio_risk as _estimate_portfolio_risk
from ._native import simulate_multi_asset_gbm_terminal_prices as _simulate_multi_asset_gbm_terminal_prices
def simulate_multi_asset_gbm_terminal_prices(
    initial_prices,
    drifts,
    volatilities,
    correlation,
    time,
    path_count,
    seed
):
    return _simulate_multi_asset_gbm_terminal_prices(
        np.asarray(initial_prices,dtype=float).tolist(),
        np.asarray(drifts,dtype=float).tolist(),
        np.asarray(volatilities,dtype=float).tolist(),
        np.asarray(correlation,dtype=float).tolist(),
        time,
        path_count,
        seed
    )
def calculate_portfolio_losses(
    terminal_prices,
    initial_prices,
    weights
):
    return _calculate_portfolio_losses(
        np.asarray(terminal_prices,dtype=float).tolist(),
        np.asarray(initial_prices,dtype=float).tolist(),
        np.asarray(weights,dtype=float).tolist()
    )
def estimate_portfolio_risk(
    terminal_prices,
    initial_prices,
    weights,
    confidence_level
):
    result=_estimate_portfolio_risk(
        np.asarray(terminal_prices,dtype=float).tolist(),
        np.asarray(initial_prices,dtype=float).tolist(),
        np.asarray(weights,dtype=float).tolist(),
        confidence_level
    )
    return {
        "value_at_risk": float(result["value_at_risk"]),
        "expected_shortfall": float(result["expected_shortfall"]),
    }