#pragma once
#include <span>
namespace riskforge::backtesting{
    [[nodiscard]]
    double maximum_drawdown(std::span<const double> log_returns);
}