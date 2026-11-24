#include "riskforge/backtesting/risk_comparison.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    RiskComparisonResult compare_risk_estimates(
        const HistoricalRiskResult& historical,
        const HistoricalRiskResult& simulated
    ){
        if (!std::isfinite(historical.value_at_risk) ||
            !std::isfinite(historical.expected_shortfall) ||
            !std::isfinite(simulated.value_at_risk) ||
            !std::isfinite(simulated.expected_shortfall)){
            throw std::invalid_argument("risk estimates must be finite");
        }
        return RiskComparisonResult{
            simulated.value_at_risk-historical.value_at_risk,
            simulated.expected_shortfall-historical.expected_shortfall
        };
    }
}