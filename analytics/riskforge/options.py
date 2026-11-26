import numpy as np
from ._native import BlackScholesInput
from ._native import black_scholes_call_delta as _call_delta
from ._native import black_scholes_call_gamma as _call_gamma
from ._native import black_scholes_call_price as _call_price
from ._native import black_scholes_call_rho as _call_rho
from ._native import black_scholes_call_theta as _call_theta
from ._native import black_scholes_call_vega as _call_vega
from ._native import black_scholes_implied_volatility as _implied_volatility
from ._native import black_scholes_put_delta as _put_delta
from ._native import black_scholes_put_gamma as _put_gamma
from ._native import black_scholes_put_price as _put_price
from ._native import black_scholes_put_rho as _put_rho
from ._native import black_scholes_put_theta as _put_theta
from ._native import black_scholes_put_vega as _put_vega
from ._native import build_call_volatility_surface as _volatility_surface
from ._native import monte_carlo_call_delta as _monte_carlo_call_delta
from ._native import monte_carlo_call_gamma as _monte_carlo_call_gamma
from ._native import monte_carlo_call_vega as _monte_carlo_call_vega
from ._native import monte_carlo_european_call_price as _monte_carlo_call_price
from ._native import monte_carlo_european_put_price as _monte_carlo_put_price
def _create_input(spot, strike, risk_free_rate, volatility, time):
    value=BlackScholesInput()
    value.spot=spot
    value.strike=strike
    value.risk_free_rate=risk_free_rate
    value.volatility=volatility
    value.time=time
    return value
def black_scholes_call_price(spot, strike, risk_free_rate, volatility, time):
    return float(_call_price(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_price(spot, strike, risk_free_rate, volatility, time):
    return float(_put_price(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_call_delta(spot, strike, risk_free_rate, volatility, time):
    return float(_call_delta(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_delta(spot, strike, risk_free_rate, volatility, time):
    return float(_put_delta(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_call_gamma(spot, strike, risk_free_rate, volatility, time):
    return float(_call_gamma(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_call_vega(spot, strike, risk_free_rate, volatility, time):
    return float(_call_vega(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_call_theta(spot, strike, risk_free_rate, volatility, time):
    return float(_call_theta(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_call_rho(spot, strike, risk_free_rate, volatility, time):
    return float(_call_rho(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_gamma(spot, strike, risk_free_rate, volatility, time):
    return float(_put_gamma(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_vega(spot, strike, risk_free_rate, volatility, time):
    return float(_put_vega(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_theta(spot, strike, risk_free_rate, volatility, time):
    return float(_put_theta(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_put_rho(spot, strike, risk_free_rate, volatility, time):
    return float(_put_rho(_create_input(spot, strike, risk_free_rate, volatility, time)))
def black_scholes_implied_volatility(spot, strike, risk_free_rate, time, market_price):
    return float(
        _implied_volatility(
            _create_input(spot, strike, risk_free_rate, 0.20, time),
            market_price
        )
    )
def build_call_volatility_surface(
    spot,
    risk_free_rate,
    volatility,
    time,
    strikes,
    market_prices
):
    result=_volatility_surface(
        _create_input(
            spot,
            strikes[0],
            risk_free_rate,
            volatility,
            time
        ),
        np.asarray(strikes,dtype=float).tolist(),
        np.asarray(market_prices,dtype=float).tolist()
    )
    return np.asarray(result,dtype=float)
def monte_carlo_european_call_price(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    strike,
    risk_free_rate,
    worker_count
):
    return float(
        _monte_carlo_call_price(
            initial_price,
            drift,
            volatility,
            time,
            path_count,
            seed,
            strike,
            risk_free_rate,
            worker_count
        )
    )
def monte_carlo_european_put_price(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    strike,
    risk_free_rate,
    worker_count
):
    return float(
        _monte_carlo_put_price(
            initial_price,
            drift,
            volatility,
            time,
            path_count,
            seed,
            strike,
            risk_free_rate,
            worker_count
        )
    )
def monte_carlo_call_delta(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    strike,
    risk_free_rate,
    worker_count,
    spot_bump
):
    return float(
        _monte_carlo_call_delta(
            initial_price,
            drift,
            volatility,
            time,
            path_count,
            seed,
            strike,
            risk_free_rate,
            worker_count,
            spot_bump
        )
    )
def monte_carlo_call_gamma(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    strike,
    risk_free_rate,
    worker_count,
    spot_bump
):
    return float(
        _monte_carlo_call_gamma(
            initial_price,
            drift,
            volatility,
            time,
            path_count,
            seed,
            strike,
            risk_free_rate,
            worker_count,
            spot_bump
        )
    )
def monte_carlo_call_vega(
    initial_price,
    drift,
    volatility,
    time,
    path_count,
    seed,
    strike,
    risk_free_rate,
    worker_count,
    volatility_bump
):
    return float(
        _monte_carlo_call_vega(
            initial_price,
            drift,
            volatility,
            time,
            path_count,
            seed,
            strike,
            risk_free_rate,
            worker_count,
            volatility_bump
        )
    )