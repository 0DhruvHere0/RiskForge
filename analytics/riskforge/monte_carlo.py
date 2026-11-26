from ._native import simulate_gbm_terminal_prices as _simulate_gbm_terminal_prices
def simulate_gbm_terminal_prices(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed
):
    return _simulate_gbm_terminal_prices(
        initial_price,
        drift,
        volatility,
        time,
        path_count,
        seed
    )