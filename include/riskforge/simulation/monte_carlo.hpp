#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace riskforge::simulation{
    struct GbmSimulationConfig{
        double initial_price;
        double drift;
        double volatility;
        double time;
        std::size_t path_count;
        std::uint32_t seed;
    };
    [[nodiscard]]
    std::vector<double> simulate_gbm_terminal_prices(
        const GbmSimulationConfig& config
    );
}