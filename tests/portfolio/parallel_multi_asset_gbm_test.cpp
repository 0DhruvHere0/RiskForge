#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include "riskforge/portfolio/parallel_multi_asset_gbm.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::MultiAssetGbmConfig;
    using riskforge::portfolio::simulate_multi_asset_gbm_terminal_prices;
    using riskforge::portfolio::simulate_multi_asset_gbm_terminal_prices_parallel;
    TEST(ParallelMultiAssetGbmTest, MatchesSerialSimulation){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            256,
            42u
        };
        const auto serial= simulate_multi_asset_gbm_terminal_prices(
            config
        );
        const auto parallel=simulate_multi_asset_gbm_terminal_prices_parallel(
            config,
            4
        );
        EXPECT_EQ(serial, parallel);
    }
    TEST(ParallelMultiAssetGbmTest, HandlesMoreWorkersThanPaths){
        const MultiAssetGbmConfig config{
            {100.0, 200.0},
            {0.05, 0.03},
            {0.20, 0.15},
            Matrix{
                {1.0, 0.5},
                {0.5, 1.0}
            },
            1.0,
            8,
            42u
        };
        const auto prices=simulate_multi_asset_gbm_terminal_prices_parallel(
            config,
            32
        );
        EXPECT_EQ(prices.size(), 8u);
        for (const auto& path : prices){
            EXPECT_EQ(path.size(), 2u);
        }
    }
}