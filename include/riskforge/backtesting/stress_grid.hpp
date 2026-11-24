#pragma once
#include "riskforge/backtesting/historical_risk.hpp"
#include <span>
#include <vector>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::vector<HistoricalRiskResult> evaluate_stress_grid(
        std::span<const double> log_returns,
        std::span<const double> additive_shocks,
        double confidence_level
    );
}