#pragma once
#include "riskforge/backtesting/historical_risk.hpp"
#include <cstddef>
#include <span>
#include <vector>
namespace riskforge::backtesting{
    [[nodiscard]]
    std::vector<HistoricalRiskResult> rolling_historical_risk(
        std::span<const double> log_returns,
        std::size_t window_size,
        double confidence_level
    );
}