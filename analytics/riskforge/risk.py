from ._native import estimate_gbm_risk as _estimate_gbm_risk
from ._native import lognormal_expected_shortfall
from ._native import lognormal_value_at_risk
def estimate_gbm_risk(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    confidence_level
):
    result=_estimate_gbm_risk(
        initial_price,
        drift,
        volatility,
        time,
        path_count,
        seed,
        confidence_level
    )
    return {
        "value_at_risk": float(result["value_at_risk"]),
        "expected_shortfall": float(result["expected_shortfall"]),
    }