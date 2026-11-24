#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::estimate_parallel_portfolio_risk;
    TEST(ParallelPortfolioRiskValidationTest, RejectsZeroWorkerCount){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            100,
            42u
        };
        const std::vector<double> weights{0.5, 0.5};
        EXPECT_THROW(
            static_cast<void>(estimate_parallel_portfolio_risk(
                config,
                weights,
                0.95,
                0
            )),
            std::invalid_argument
        );
    }
    TEST(ParallelPortfolioRiskValidationTest, RejectsInvalidConfidence){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            100,
            42u
        };
        const std::vector<double> weights{0.5, 0.5};
        EXPECT_THROW(
            static_cast<void>(estimate_parallel_portfolio_risk(
                config,
                weights,
                1.0,
                2
            )),
            std::invalid_argument
        );
    }
    TEST(ParallelPortfolioRiskValidationTest, RejectsMismatchedWeights){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            100,
            42u
        };
        const std::vector<double> weights{1.0};
        EXPECT_THROW(
            static_cast<void>(estimate_parallel_portfolio_risk(
                config,
                weights,
                0.95,
                2
            )),
            std::invalid_argument
        );
    }
}