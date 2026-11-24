#pragma once
#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include "riskforge/portfolio/portfolio_risk.hpp"
#include <cstddef>
#include <vector>
namespace riskforge::portfolio{
    struct PortfolioEngineConfig{
        MultiAssetGbmConfig simulation;
        std::vector<double> weights;
        double confidence_level;
        std::size_t worker_count;
    };
    [[nodiscard]]
    PortfolioRiskResult run_portfolio_risk(
        const PortfolioEngineConfig& config
    );
}