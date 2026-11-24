#pragma once
#include "riskforge/backtesting/historical_risk.hpp"
#include <span>
namespace riskforge::backtesting{
    [[nodiscard]]
    HistoricalRiskResult estimate_stressed_risk(
        std::span<const double> log_returns,
        double additive_shock,
        double confidence_level
    );
}