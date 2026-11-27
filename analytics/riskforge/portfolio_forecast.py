from dataclasses import dataclass
import numpy as np
from .simulation import gbm_terminal_price
@dataclass(frozen=True)
class ForecastHolding:
    symbol: str
    current_price: float
    drift: float
    volatility: float
@dataclass(frozen=True)
class PortfolioForecast:
    time: float
    prices: dict[str, np.ndarray]
def _default_simulator(
    initial_price: float,
    drift: float,
    volatility: float,
    time: float,
    path_count: int,
    seed: int
):
    generator=np.random.default_rng(seed)
    shocks=generator.standard_normal(path_count)
    return np.asarray(
        [
            gbm_terminal_price(
                initial_price,
                drift,
                volatility,
                time,
                float(shock)
            )
            for shock in shocks
        ],
        dtype=float
    )
class PortfolioForecaster:
    def __init__(self, simulator=_default_simulator):
        self._simulator=simulator
    def forecast(
        self,
        holdings: list[ForecastHolding],
        time: float,
        path_count: int,
        seed: int
    ) -> PortfolioForecast:
        if not holdings:
            raise ValueError("holdings must not be empty")
        if time<=0.0:
            raise ValueError("time must be positive")
        if path_count<=0:
            raise ValueError("path_count must be positive")
        symbols={holding.symbol for holding in holdings}
        if len(symbols)!=len(holdings):
            raise ValueError("holding symbols must be unique")
        prices={}
        for holding in holdings:
            if holding.current_price<=0.0:
                raise ValueError("current price must be positive")
            if holding.volatility<0.0:
                raise ValueError("volatility must be non-negative")
            prices[holding.symbol]=np.asarray(
                self._simulator(
                    holding.current_price,
                    holding.drift,
                    holding.volatility,
                    time,
                    path_count,
                    seed
                ),
                dtype=float
            )
        return PortfolioForecast(
            time=time,
            prices=prices
        )