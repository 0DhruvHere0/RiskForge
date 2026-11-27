from dataclasses import dataclass
import numpy as np
from .portfolio_forecast import PortfolioForecast
from .portfolio_forecast import ForecastHolding
@dataclass(frozen=True)
class PortfolioForecastSummary:
    expected_value: float
    lower_value: float
    median_value: float
    upper_value: float
    values: np.ndarray
def summarize_portfolio_forecast(
    forecast: PortfolioForecast,
    holdings: list[ForecastHolding],
    quantities: dict[str, float],
    lower_probability: float=0.05,
    upper_probability: float=0.95
) -> PortfolioForecastSummary:
    if not holdings:
        raise ValueError("holdings must not be empty")
    if not 0.0<lower_probability<upper_probability<1.0:
        raise ValueError("probabilities must satisfy 0 < lower < upper < 1")
    if set(forecast.prices)!={holding.symbol for holding in holdings}:
        raise ValueError("forecast symbols do not match holdings")
    path_count=len(next(iter(forecast.prices.values())))
    values=np.zeros(path_count, dtype=float)
    for holding in holdings:
        if holding.symbol not in quantities:
            raise ValueError("quantity is missing")
        quantity=quantities[holding.symbol]
        if quantity<=0.0:
            raise ValueError("quantity must be positive")
        values+=forecast.prices[holding.symbol]*quantity
    return PortfolioForecastSummary(
        expected_value=float(np.mean(values)),
        lower_value=float(np.quantile(values, lower_probability)),
        median_value=float(np.quantile(values, 0.50)),
        upper_value=float(np.quantile(values, upper_probability)),
        values=values
    )