#pragma once
#include "riskforge/backtesting/backtest_report.hpp"
#include <cstddef>
#include <span>
#include <vector>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::vector<BacktestReport> rolling_backtest_reports(
        std::span<const double> log_returns,
        std::size_t window_size,
        double value_at_risk,
        double periods_per_year
    );
}