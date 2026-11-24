#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
#include "riskforge/portfolio/portfolio_risk.hpp"
#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::estimate_parallel_portfolio_risk;
    using riskforge::portfolio::estimate_portfolio_risk;
    using riskforge::portfolio::simulate_multi_asset_gbm_terminal_prices;
    TEST(ParallelPortfolioRiskTest, MatchesSerialRiskEstimation){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            2000,
            42u
        };
        const std::vector<double> weights{0.5, 0.5};
        const auto terminal_prices=simulate_multi_asset_gbm_terminal_prices(config);
        const auto serial=estimate_portfolio_risk(
            terminal_prices,
            config.initial_prices,
            weights,
            0.95
        );
        const auto parallel=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            4
        );
        EXPECT_DOUBLE_EQ(
            serial.value_at_risk,
            parallel.value_at_risk
        );
        EXPECT_DOUBLE_EQ(
            serial.expected_shortfall,
            parallel.expected_shortfall
        );
    }
    TEST(ParallelPortfolioRiskTest, ProducesFiniteRiskMeasures){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            2000,
            42u
        };
        const std::vector<double> weights{0.5, 0.5};
        const auto result=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            4
        );
        EXPECT_TRUE(std::isfinite(result.value_at_risk));
        EXPECT_TRUE(std::isfinite(result.expected_shortfall));
        EXPECT_GE(
            result.expected_shortfall,
            result.value_at_risk
        );
    }
}