#pragma once
#include <span>
#include <vector>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::vector<double> apply_return_shock(
        std::span<const double> log_returns,
        double additive_shock
    );
}