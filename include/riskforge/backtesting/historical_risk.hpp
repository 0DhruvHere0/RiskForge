#pragma once
#include <span>
namespace riskforge::backtesting{
    struct HistoricalRiskResult{
        double value_at_risk;
        double expected_shortfall;
    };
    [[nodiscard]]
    HistoricalRiskResult estimate_historical_risk(
        std::span<const double> log_returns,
        double confidence_level
    );
}