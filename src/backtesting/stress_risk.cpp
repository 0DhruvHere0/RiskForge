#include "riskforge/backtesting/stress_risk.hpp"
#include "riskforge/backtesting/stress_scenario.hpp"
namespace riskforge::backtesting{
    HistoricalRiskResult estimate_stressed_risk(
        std::span<const double> log_returns,
        double additive_shock,
        double confidence_level
    ){
        const auto stressed_returns=apply_return_shock(
            log_returns,
            additive_shock
        );
        return estimate_historical_risk(
            stressed_returns,
            confidence_level
        );
    }
}