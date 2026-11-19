#include "riskforge/risk/monte_carlo_risk.hpp"
#include "riskforge/risk/tail.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
namespace riskforge::risk {
    MonteCarloRiskResult estimate_gbm_risk(
        const simulation::GbmSimulationConfig& config,
        double confidence_level
    ){
        if (!std::isfinite(confidence_level)|| confidence_level<= 0.0|| confidence_level>= 1.0){
            throw std::invalid_argument("confidence_level must be between 0 and 1");
        }
        const auto terminal_prices= simulation::simulate_gbm_terminal_prices(config);
        std::vector<double> losses;
        losses.reserve(terminal_prices.size());
        for (const double terminal_price: terminal_prices) {losses.push_back(
                config.initial_price - terminal_price);
        }
        const TailSummary summary= aggregate_upper_tail(
                losses,
                1.0 - confidence_level
        );
        return MonteCarloRiskResult{
            summary.threshold,
            summary.sum/ static_cast<double>(summary.count)
        };
    }
}