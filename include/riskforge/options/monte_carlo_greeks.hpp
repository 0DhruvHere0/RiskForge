#pragma once
#include "riskforge/simulation/monte_carlo.hpp"
#include <cstddef>
namespace riskforge::options{
    [[nodiscard]]
    double monte_carlo_call_delta(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double spot_bump);
    [[nodiscard]]
    double monte_carlo_call_gamma(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double spot_bump);
    [[nodiscard]]
    double monte_carlo_call_vega(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double volatility_bump);
}