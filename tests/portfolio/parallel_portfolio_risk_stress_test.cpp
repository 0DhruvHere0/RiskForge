#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::estimate_parallel_portfolio_risk;
    TEST(ParallelPortfolioRiskStressTest, HandlesLargePortfolioSimulation){
        const MultiAssetGbmConfig config{
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
        };
        const std::vector<double> weights{0.4, 0.3, 0.3};
        const auto result=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            8
        );
        EXPECT_TRUE(std::isfinite(result.value_at_risk));
        EXPECT_TRUE(std::isfinite(result.expected_shortfall));
        EXPECT_GE(result.expected_shortfall, result.value_at_risk);
    }
}