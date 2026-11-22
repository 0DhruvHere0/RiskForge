#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::simulate_multi_asset_gbm_terminal_prices;
    TEST(MultiAssetGbmTest, ProducesRequestedPathsAndAssets){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.0},
                {0.0, 1.0}
            },
            1.0,
            128,
            42u
        };
        const auto prices= simulate_multi_asset_gbm_terminal_prices(config);
        ASSERT_EQ(prices.size(), 128u);
        for (const auto& path : prices){
            EXPECT_EQ(path.size(), 2u);
        }
    }
    TEST(MultiAssetGbmTest, ZeroVolatilityProducesDeterministicPrices){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.0, 0.0},
            Matrix{
                {1.0, 0.0},
                {0.0, 1.0}
            },
            1.0,
            8,
            42u
        };
        const auto prices= simulate_multi_asset_gbm_terminal_prices(config);
        for (const auto& path : prices){
            EXPECT_NEAR(
                path[0],
                105.12710963760242,
                1e-12
            );
            EXPECT_NEAR(
                path[1],
                206.0909067907034,
                1e-12
            );
        }
    }
    TEST(MultiAssetGbmTest, SameSeedProducesSamePaths){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            32,
            42u
        };
        const auto first= simulate_multi_asset_gbm_terminal_prices(config);
        const auto second= simulate_multi_asset_gbm_terminal_prices(config);
        EXPECT_EQ(first, second);
    }
}