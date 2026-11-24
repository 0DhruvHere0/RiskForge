#pragma once
#include "riskforge/simulation/monte_carlo.hpp"
#include <cstddef>
namespace riskforge::options{
    [[nodiscard]]
    double monte_carlo_european_call_price(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count);
    [[nodiscard]]
    double monte_carlo_european_put_price(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count);
}