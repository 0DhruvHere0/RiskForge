#include "riskforge/simulation/monte_carlo.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <vector>
namespace{
    using riskforge::simulation::GbmSimulationConfig;
    using riskforge::simulation::simulate_gbm_terminal_prices;
    TEST(MonteCarloTest, ProducesRequestedNumberOfPaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            128,
            42u
        };
        const auto prices= simulate_gbm_terminal_prices(config);
        EXPECT_EQ(prices.size(), 128u);
    }
    TEST(MonteCarloTest, SameSeedProducesSamePaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            32,
            42u
        };
        const auto first= simulate_gbm_terminal_prices(config);
        const auto second= simulate_gbm_terminal_prices(config);
        ASSERT_EQ(first.size(), second.size());
        for (std::size_t index=0; index<first.size(); ++index){
            EXPECT_DOUBLE_EQ(first[index], second[index]);
        }
    }
    TEST(MonteCarloTest, DifferentSeedsProduceDifferentPaths){
        const GbmSimulationConfig first_config{
            100.0,
            0.05,
            0.20,
            1.0,
            32,
            42u
        };
        const GbmSimulationConfig second_config{
            100.0,
            0.05,
            0.20,
            1.0,
            32,
            43u
        };
        const auto first= simulate_gbm_terminal_prices(first_config);
        const auto second= simulate_gbm_terminal_prices(second_config);
        EXPECT_NE(first, second);
    }
    TEST(MonteCarloTest, ZeroVolatilityProducesDeterministicPaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.0,
            1.0,
            16,
            42u
        };
        const auto prices= simulate_gbm_terminal_prices(config);
        ASSERT_EQ(prices.size(), 16u);
        for (const double price: prices){
            EXPECT_NEAR(price, 105.12710963760242, 1e-12);
        }
    }
}