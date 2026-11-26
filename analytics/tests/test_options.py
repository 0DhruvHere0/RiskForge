import math
from riskforge import black_scholes_call_price
from riskforge import black_scholes_put_price
from riskforge import black_scholes_call_delta
from riskforge import black_scholes_call_gamma
def test_black_scholes_prices_are_finite():
    call=black_scholes_call_price(
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    )
    put=black_scholes_put_price(
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    )
    assert math.isfinite(call)
    assert math.isfinite(put)
    assert call>0.0
    assert put>0.0
def test_black_scholes_greeks_are_finite():
    delta=black_scholes_call_delta(
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    )
    gamma=black_scholes_call_gamma(
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    )
    assert math.isfinite(delta)
    assert math.isfinite(gamma)
    assert 0.0<delta<1.0
    assert gamma>0.0