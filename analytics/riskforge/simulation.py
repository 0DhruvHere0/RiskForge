from ._native import gbm_terminal_price as _gbm_terminal_price
def gbm_terminal_price(
    initial_price,
    drift,
    volatility,
    time,
    standard_normal
):
    return float(
        _gbm_terminal_price(
            initial_price,
            drift,
            volatility,
            time,
            standard_normal
        )
    )