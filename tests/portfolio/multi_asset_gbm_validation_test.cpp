#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::simulate_multi_asset_gbm_terminal_prices;
    TEST(MultiAssetGbmValidationTest, RejectsEmptyAssets){
        const MultiAssetGbmConfig config{
            {},
            {},
            {},
            Matrix{},
            1.0,
            10,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_multi_asset_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
    TEST(MultiAssetGbmValidationTest, RejectsMismatchedParameters){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.0},
                {0.0, 1.0}
            },
            1.0,
            10,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_multi_asset_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
    TEST(MultiAssetGbmValidationTest, RejectsZeroPathCount){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.0},
                {0.0, 1.0}
            },
            1.0,
            0,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_multi_asset_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
}