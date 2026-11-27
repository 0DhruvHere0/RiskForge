import numpy as np
import pytest
from riskforge.portfolio_forecast import ForecastHolding
from riskforge.portfolio_forecast import PortfolioForecast
from riskforge.portfolio_forecast_analysis import summarize_portfolio_forecast
def test_summarizes_portfolio_forecast():
    holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        ),
        ForecastHolding(
            symbol="BBB",
            current_price=200.0,
            drift=0.03,
            volatility=0.15
        )
    ]
    forecast=PortfolioForecast(
        time=10.0,
        prices={
            "AAA": np.asarray([100.0, 110.0, 120.0]),
            "BBB": np.asarray([200.0, 210.0, 220.0])
        }
    )
    result=summarize_portfolio_forecast(
        forecast,
        holdings,
        {
            "AAA": 2.0,
            "BBB": 1.0
        }
    )
    np.testing.assert_allclose(
        result.values,
        np.asarray([400.0, 430.0, 460.0])
    )
    assert result.expected_value==430.0
    assert result.median_value==430.0
def test_rejects_missing_quantity():
    holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        )
    ]
    forecast=PortfolioForecast(
        time=10.0,
        prices={"AAA": np.asarray([100.0, 110.0])}
    )
    with pytest.raises(ValueError):
        summarize_portfolio_forecast(
            forecast,
            holdings,
            {}
        )
def test_rejects_invalid_probability_range():
    holdings=[
        ForecastHolding(
            symbol="AAA",
            current_price=100.0,
            drift=0.05,
            volatility=0.20
        )
    ]
    forecast=PortfolioForecast(
        time=10.0,
        prices={"AAA": np.asarray([100.0, 110.0])}
    )
    with pytest.raises(ValueError):
        summarize_portfolio_forecast(
            forecast,
            holdings,
            {"AAA": 1.0},
            0.95,
            0.05
        )