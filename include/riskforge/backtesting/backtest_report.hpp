#pragma once
#include "riskforge/backtesting/var_backtest.hpp"
#include <span>
namespace riskforge::backtesting{
    struct BacktestReport{
        VarBacktestResult value_at_risk_backtest;
        double maximum_drawdown;
        double annualized_volatility;
    };
    [[nodiscard]]
    BacktestReport create_backtest_report(
        std::span<const double> log_returns,
        double value_at_risk,
        double periods_per_year
    );
}