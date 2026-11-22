#pragma once
#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include <cstddef>
#include <vector>
namespace riskforge::portfolio{
    [[nodiscard]]
    std::vector<std::vector<double>>
    simulate_multi_asset_gbm_terminal_prices_parallel(
        const MultiAssetGbmConfig& config,
        std::size_t worker_count
    );
}