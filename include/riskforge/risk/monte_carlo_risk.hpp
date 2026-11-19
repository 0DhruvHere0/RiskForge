#pragma once
#include "riskforge/simulation/monte_carlo.hpp"
namespace riskforge::risk{
    struct MonteCarloRiskResult {
        double value_at_risk;
        double expected_shortfall;
    };
    [[nodiscard]]
    MonteCarloRiskResult estimate_gbm_risk(
        const simulation::GbmSimulationConfig& config,
        double confidence_level
    );
}