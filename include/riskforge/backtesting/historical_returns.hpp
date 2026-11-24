#pragma once
#include <span>
#include <vector>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::vector<double> historical_log_returns(std::span<const double> prices);
}