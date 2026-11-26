import math
from riskforge import monte_carlo_call_delta
from riskforge import monte_carlo_call_gamma
from riskforge import monte_carlo_call_vega
from riskforge import monte_carlo_european_call_price
from riskforge import monte_carlo_european_put_price
def test_monte_carlo_option_prices_are_finite():
    call=monte_carlo_european_call_price(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        100.0,
        0.05,
        2
    )
    put=monte_carlo_european_put_price(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        100.0,
        0.05,
        2
    )
    assert math.isfinite(call)
    assert math.isfinite(put)
    assert call>0.0
    assert put>0.0
def test_monte_carlo_greeks_are_finite():
    delta=monte_carlo_call_delta(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        100.0,
        0.05,
        2,
        0.01
    )
    gamma=monte_carlo_call_gamma(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        100.0,
        0.05,
        2,
        0.01
    )
    vega=monte_carlo_call_vega(
        100.0,
        0.05,
        0.20,
        1.0,
        1000,
        42,
        100.0,
        0.05,
        2,
        0.01
    )
    assert math.isfinite(delta)
    assert math.isfinite(gamma)
    assert math.isfinite(vega)