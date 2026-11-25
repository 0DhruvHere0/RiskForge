from riskforge import gbm_terminal_price
def test_gbm_deterministic_growth():
    result=gbm_terminal_price(
        100.0,
        0.05,
        0.0,
        1.0,
        0.0
    )
    assert abs(result-105.12710963760242)<1e-12