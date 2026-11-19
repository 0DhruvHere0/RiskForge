#pragma once
#include "riskforge/risk/monte_carlo_risk.hpp"
#include "riskforge/simulation/monte_carlo.hpp"
#include <cstddef>
namespace riskforge::risk {
    [[nodiscard]]
    MonteCarloRiskResult estimate_gbm_risk_parallel(
        const simulation::GbmSimulationConfig& config,
        double confidence_level,
        std::size_t worker_count
    );
}