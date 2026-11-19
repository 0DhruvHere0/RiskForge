#pragma once
#include "riskforge/simulation/monte_carlo.hpp"
#include <cstddef>
#include <vector>
namespace riskforge::simulation{
    [[nodiscard]]
    std::vector<double> simulate_gbm_terminal_prices_parallel(
        const GbmSimulationConfig& config,
        std::size_t worker_count
    );
}