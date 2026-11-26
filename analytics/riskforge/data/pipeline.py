import numpy as np
from ..backtesting import estimate_historical_risk
from ..backtesting import historical_log_returns
from .models import HistoricalPriceSeries
def price_series_to_log_returns(series: HistoricalPriceSeries):
    if not isinstance(series, HistoricalPriceSeries):
        raise TypeError("series must be a HistoricalPriceSeries")
    return historical_log_returns(series.closes)
def estimate_series_historical_risk(
    series: HistoricalPriceSeries,
    confidence_level: float
):
    log_returns=price_series_to_log_returns(series)
    result=estimate_historical_risk(
        log_returns,
        confidence_level
    )
    return {
        "symbol": series.symbol,
        "value_at_risk": result["value_at_risk"],
        "expected_shortfall": result["expected_shortfall"],
        "log_returns": np.asarray(log_returns,dtype=float),
    }