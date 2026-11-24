#pragma once
#include "riskforge/backtesting/historical_risk.hpp"
namespace riskforge::backtesting{
    struct RiskComparisonResult{
        double value_at_risk_difference;
        double expected_shortfall_difference;
    };
    [[nodiscard]]
    RiskComparisonResult compare_risk_estimates(
        const HistoricalRiskResult& historical,
        const HistoricalRiskResult& simulated
    );
}