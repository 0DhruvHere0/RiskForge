import numpy as np
from ._native import jump_diffusion_terminal_price
from ._native import parallel_stochastic_volatility_terminal_prices
from ._native import stochastic_volatility_terminal_price
from ._native import student_t_gbm_terminal_price
def student_t_gbm_price(
    initial_price,
    drift,
    volatility,
    time,
    degrees_of_freedom,
    seed,
    sample
):
    return float(
        student_t_gbm_terminal_price(
            initial_price,
            drift,
            volatility,
            time,
            degrees_of_freedom,
            seed,
            sample
        )
    )
def stochastic_volatility_price(
    initial_price,
    drift,
    initial_variance,
    long_term_variance,
    mean_reversion,
    volatility_of_variance,
    time,
    steps,
    seed,
    sample
):
    return float(
        stochastic_volatility_terminal_price(
            initial_price,
            drift,
            initial_variance,
            long_term_variance,
            mean_reversion,
            volatility_of_variance,
            time,
            steps,
            seed,
            sample
        )
    )
def parallel_stochastic_volatility_prices(
    initial_price,
    drift,
    initial_variance,
    long_term_variance,
    mean_reversion,
    volatility_of_variance,
    time,
    steps,
    path_count,
    worker_count,
    seed
):
    return parallel_stochastic_volatility_terminal_prices(
        initial_price,
        drift,
        initial_variance,
        long_term_variance,
        mean_reversion,
        volatility_of_variance,
        time,
        steps,
        path_count,
        worker_count,
        seed
    )
def jump_diffusion_price(
    initial_price,
    drift,
    volatility,
    jump_intensity,
    jump_mean,
    jump_volatility,
    time,
    seed,
    sample
):
    return float(
        jump_diffusion_terminal_price(
            initial_price,
            drift,
            volatility,
            jump_intensity,
            jump_mean,
            jump_volatility,
            time,
            seed,
            sample
        )
    )