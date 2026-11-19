#include "riskforge/risk/parallel_monte_carlo_risk.hpp"
#include "riskforge/risk/monte_carlo_risk.hpp"
#include "riskforge/risk/tail_accumulator.hpp"
#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::risk{
    MonteCarloRiskResult estimate_gbm_risk_parallel(
        const simulation::GbmSimulationConfig& config,
        double confidence_level,
        std::size_t worker_count
    ){
        if (!std::isfinite(confidence_level) ||
            confidence_level <= 0.0 ||
            confidence_level >= 1.0){
            throw std::invalid_argument(
                "confidence_level must be between 0 and 1"
            );
        }
        if (worker_count == 0){
            throw std::invalid_argument(
                "worker_count must be greater than zero"
            );
        }
        const auto terminal_prices=
            simulation::simulate_gbm_terminal_prices_parallel(
                config,
                worker_count
            );
        AdaptiveTailAccumulator accumulator(
            config.path_count,
            1.0-confidence_level
        );
        for (const double terminal_price : terminal_prices){
            accumulator.add(
                config.initial_price-terminal_price
            );
        }
        const TailSummary summary= accumulator.finalize();
        return MonteCarloRiskResult{
            summary.threshold,
            summary.sum/static_cast<double>(summary.count)
        };
    }
}