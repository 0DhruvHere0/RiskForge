#include "riskforge/backtesting/stress_grid.hpp"
#include "riskforge/backtesting/stress_risk.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    std::vector<HistoricalRiskResult> evaluate_stress_grid(
        std::span<const double> log_returns,
        std::span<const double> additive_shocks,
        double confidence_level
    ){
        if (additive_shocks.empty()){
            throw std::invalid_argument("additive_shocks must not be empty");
        }
        std::vector<HistoricalRiskResult> results;
        results.reserve(additive_shocks.size());
        for (const double additive_shock: additive_shocks){
            if (!std::isfinite(additive_shock)){
                throw std::invalid_argument("additive_shocks must be finite");
            }
            results.push_back(
                estimate_stressed_risk(
                    log_returns,
                    additive_shock,
                    confidence_level
                )
            );
        }
        return results;
    }
}