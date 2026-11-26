import math
import numpy as np
from riskforge import jump_diffusion_price
from riskforge import parallel_stochastic_volatility_prices
from riskforge import stochastic_volatility_price
from riskforge import student_t_gbm_price
def test_advanced_terminal_prices_are_finite():
    student_t_price=student_t_gbm_price(
        100.0,
        0.05,
        0.20,
        1.0,
        8.0,
        42,
        0
    )
    stochastic_price=stochastic_volatility_price(
        100.0,
        0.05,
        0.04,
        0.04,
        2.0,
        0.20,
        1.0,
        100,
        42,
        0
    )
    jump_price=jump_diffusion_price(
        100.0,
        0.05,
        0.20,
        0.10,
        -0.05,
        0.10,
        1.0,
        42,
        0
    )
    assert math.isfinite(student_t_price)
    assert math.isfinite(stochastic_price)
    assert math.isfinite(jump_price)
    assert student_t_price>0.0
    assert stochastic_price>0.0
    assert jump_price>0.0
def test_parallel_stochastic_volatility_shape():
    prices=parallel_stochastic_volatility_prices(
        100.0,
        0.05,
        0.04,
        0.04,
        2.0,
        0.20,
        1.0,
        100,
        50,
        2,
        42
    )
    assert isinstance(prices, np.ndarray)
    assert prices.shape==(50,)
    assert np.all(np.isfinite(prices))
    assert np.all(prices>0.0)