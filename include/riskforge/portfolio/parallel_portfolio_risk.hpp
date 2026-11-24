#pragma once
#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include "riskforge/portfolio/portfolio_risk.hpp"
#include <cstddef>
#include <vector>
namespace riskforge::portfolio{
    [[nodiscard]]
    PortfolioRiskResult estimate_parallel_portfolio_risk(
        const MultiAssetGbmConfig& config,
        const std::vector<double>& weights,
        double confidence_level,
        std::size_t worker_count
    );
}