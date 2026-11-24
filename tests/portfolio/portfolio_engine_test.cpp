#include "riskforge/portfolio/portfolio_engine.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::PortfolioEngineConfig;
    using riskforge::portfolio::run_portfolio_risk;
    TEST(PortfolioEngineTest, RunsCompletePortfolioRiskPipeline){
        const PortfolioEngineConfig config{
            MultiAssetGbmConfig{
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
            },
            {0.5, 0.5},
            0.95,
            4
        };
        const auto result=run_portfolio_risk(config);
        EXPECT_TRUE(std::isfinite(result.value_at_risk));
        EXPECT_TRUE(std::isfinite(result.expected_shortfall));
        EXPECT_GE(result.expected_shortfall, result.value_at_risk);
    }
    TEST(PortfolioEngineTest, IsDeterministic){
        const PortfolioEngineConfig config{
            MultiAssetGbmConfig{
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
            },
            {0.5, 0.5},
            0.95,
            4
        };
        const auto first=run_portfolio_risk(config);
        const auto second=run_portfolio_risk(config);
        EXPECT_DOUBLE_EQ(first.value_at_risk, second.value_at_risk);
        EXPECT_DOUBLE_EQ(first.expected_shortfall, second.expected_shortfall);
    }
}