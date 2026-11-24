#include "riskforge/portfolio/portfolio_engine.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::PortfolioEngineConfig;
    using riskforge::portfolio::run_portfolio_risk;
    TEST(PortfolioEngineValidationTest, RejectsZeroWorkers){
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
                100,
                42u
            },
            {0.5, 0.5},
            0.95,
            0
        };
        EXPECT_THROW(
            static_cast<void>(run_portfolio_risk(config)),
            std::invalid_argument
        );
    }
    TEST(PortfolioEngineValidationTest, RejectsInvalidConfidence){
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
                100,
                42u
            },
            {0.5, 0.5},
            1.0,
            2
        };
        EXPECT_THROW(
            static_cast<void>(run_portfolio_risk(config)),
            std::invalid_argument
        );
    }
}