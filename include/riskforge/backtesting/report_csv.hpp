#pragma once
#include "riskforge/backtesting/backtest_report.hpp"
#include <string>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::string backtest_report_to_csv(const BacktestReport& report);
}