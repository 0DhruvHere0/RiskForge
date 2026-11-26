import numpy as np
from riskforge import backtest_value_at_risk
from riskforge import calculate_performance_metrics
from riskforge import create_backtest_report
from riskforge import estimate_historical_risk
from riskforge import historical_log_returns
def test_historical_returns_and_risk():
    prices=np.array([
        100.0,
        105.0,
        95.0,
        110.0,
        90.0
    ])
    returns=historical_log_returns(prices)
    risk=estimate_historical_risk(returns, 0.75)
    assert returns.shape==(4,)
    assert np.all(np.isfinite(returns))
    assert risk["expected_shortfall"]>=risk["value_at_risk"]
def test_backtesting_report():
    log_returns=np.array([
        0.01,
        -0.02,
        -0.08,
        -0.12,
        0.02
    ])
    backtest=backtest_value_at_risk(log_returns, 0.08)
    metrics=calculate_performance_metrics(log_returns, 252.0)
    report=create_backtest_report(log_returns, 0.08, 252.0)
    assert backtest["observation_count"]==5
    assert backtest["exception_count"]==1
    assert np.isfinite(metrics["annualized_return"])
    assert np.isfinite(report["maximum_drawdown"])
    assert np.isfinite(report["annualized_volatility"])