import numpy as np
from ._native import backtest_value_at_risk as _backtest_value_at_risk
from ._native import calculate_performance_metrics as _calculate_performance_metrics
from ._native import create_backtest_report as _create_backtest_report
from ._native import estimate_historical_risk as _estimate_historical_risk
from ._native import historical_log_returns as _historical_log_returns
def historical_log_returns(prices):
    return _historical_log_returns(
        np.asarray(prices,dtype=float).tolist()
    )
def estimate_historical_risk(log_returns, confidence_level):
    result=_estimate_historical_risk(
        np.asarray(log_returns,dtype=float).tolist(),
        confidence_level
    )
    return {
        "value_at_risk": float(result["value_at_risk"]),
        "expected_shortfall": float(result["expected_shortfall"]),
    }
def backtest_value_at_risk(log_returns, value_at_risk):
    result=_backtest_value_at_risk(
        np.asarray(log_returns,dtype=float).tolist(),
        value_at_risk
    )
    return {
        "observation_count": int(result["observation_count"]),
        "exception_count": int(result["exception_count"]),
        "exception_rate": float(result["exception_rate"]),
    }
def calculate_performance_metrics(log_returns, periods_per_year):
    result=_calculate_performance_metrics(
        np.asarray(log_returns,dtype=float).tolist(),
        periods_per_year
    )
    return {
        "total_log_return": float(result["total_log_return"]),
        "total_compounded_return": float(
            result["total_compounded_return"]
        ),
        "annualized_return": float(result["annualized_return"]),
    }
def create_backtest_report(log_returns, value_at_risk, periods_per_year):
    result=_create_backtest_report(
        np.asarray(log_returns,dtype=float).tolist(),
        value_at_risk,
        periods_per_year
    )
    return {
        "observation_count": int(result["observation_count"]),
        "exception_count": int(result["exception_count"]),
        "exception_rate": float(result["exception_rate"]),
        "maximum_drawdown": float(result["maximum_drawdown"]),
        "annualized_volatility": float(
            result["annualized_volatility"]
        ),
    }