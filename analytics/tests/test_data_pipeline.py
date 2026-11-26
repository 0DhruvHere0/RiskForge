import numpy as np
from riskforge.data import HistoricalPriceSeries
from riskforge.data import estimate_series_historical_risk
from riskforge.data import price_series_to_log_returns
def test_price_series_to_log_returns():
    series=HistoricalPriceSeries(
        symbol="TEST",
        dates=[
            "2025-01-01",
            "2025-01-02",
            "2025-01-03",
        ],
        closes=np.array([
            100.0,
            110.0,
            99.0,
        ])
    )
    returns=price_series_to_log_returns(series)
    assert returns.shape==(2,)
    assert np.all(np.isfinite(returns))
def test_estimate_series_historical_risk():
    series=HistoricalPriceSeries(
        symbol="TEST",
        dates=[
            "2025-01-01",
            "2025-01-02",
            "2025-01-03",
            "2025-01-04",
        ],
        closes=np.array([
            100.0,
            105.0,
            95.0,
            90.0,
        ])
    )
    result=estimate_series_historical_risk(series, 0.75)
    assert result["symbol"]=="TEST"
    assert np.isfinite(result["value_at_risk"])
    assert np.isfinite(result["expected_shortfall"])
    assert result["expected_shortfall"]>=result["value_at_risk"]