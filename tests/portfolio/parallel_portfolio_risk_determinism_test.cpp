#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::estimate_parallel_portfolio_risk;
    TEST(ParallelPortfolioRiskDeterminismTest, SameSeedProducesSameRisk){
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
        const auto first=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            4
        );
        const auto second=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            4
        );
        EXPECT_DOUBLE_EQ(first.value_at_risk, second.value_at_risk);
        EXPECT_DOUBLE_EQ(first.expected_shortfall, second.expected_shortfall);
    }
    TEST(ParallelPortfolioRiskDeterminismTest, WorkerCountDoesNotChangeRisk){
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
        const auto two_workers=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            2
        );
        const auto four_workers=estimate_parallel_portfolio_risk(
            config,
            weights,
            0.95,
            4
        );
        EXPECT_DOUBLE_EQ(two_workers.value_at_risk, four_workers.value_at_risk);
        EXPECT_DOUBLE_EQ(two_workers.expected_shortfall, four_workers.expected_shortfall);
    }
}