import math
from riskforge import estimate_gbm_risk
from riskforge import lognormal_expected_shortfall
from riskforge import lognormal_value_at_risk
def test_lognormal_risk_is_finite():
    value_at_risk=lognormal_value_at_risk(
        100.0,
        0.05,
        0.20,
        1.0,
        0.95
    )
    expected_shortfall=lognormal_expected_shortfall(
        100.0,
        0.05,
        0.20,
        1.0,
        0.95
    )
    assert math.isfinite(value_at_risk)
    assert math.isfinite(expected_shortfall)
    assert expected_shortfall>=value_at_risk
def test_monte_carlo_risk_returns_expected_fields():
    result=estimate_gbm_risk(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        0.95
    )
    assert set(result)=={
        "value_at_risk",
        "expected_shortfall",
    }
    assert math.isfinite(result["value_at_risk"])
    assert math.isfinite(result["expected_shortfall"])