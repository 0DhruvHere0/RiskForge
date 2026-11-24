#include "riskforge/portfolio/portfolio_engine.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::PortfolioEngineConfig;
    using riskforge::portfolio::run_portfolio_risk;
    TEST(PortfolioEngineStressTest, HandlesLargePortfolio){
        const PortfolioEngineConfig config{
            MultiAssetGbmConfig{
                {100.0, 200.0, 150.0},
                {0.05, 0.03, 0.04},
                {0.20, 0.15, 0.18},
                Matrix{
                    {1.0, 0.5, 0.2},
                    {0.5, 1.0, 0.3},
                    {0.2, 0.3, 1.0}
                },
                1.0,
                10'000,
                42u
            },
            {0.4, 0.3, 0.3},
            0.95,
            8
        };
        const auto result=run_portfolio_risk(config);
        EXPECT_TRUE(std::isfinite(result.value_at_risk));
        EXPECT_TRUE(std::isfinite(result.expected_shortfall));
        EXPECT_GE(result.expected_shortfall, result.value_at_risk);
    }
}