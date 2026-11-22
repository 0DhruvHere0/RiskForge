#pragma once
#include "riskforge/portfolio/correlation.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
namespace riskforge::portfolio{
    struct MultiAssetGbmConfig{
        std::vector<double> initial_prices;
        std::vector<double> drifts;
        std::vector<double> volatilities;
        Matrix correlation;
        double time;
        std::size_t path_count;
        std::uint32_t seed;
    };
    [[nodiscard]]
    std::vector<std::vector<double>>
    simulate_multi_asset_gbm_terminal_prices(const MultiAssetGbmConfig& config);
}