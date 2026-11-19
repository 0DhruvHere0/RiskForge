#include "riskforge/simulation/monte_carlo.hpp"
#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::GbmSimulationConfig;
    using riskforge::simulation::
        simulate_gbm_terminal_prices;
    using riskforge::simulation::
        simulate_gbm_terminal_prices_parallel;
    TEST(ParallelMonteCarloStressTest, HandlesMoreWorkersThanPaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            32,
            42u
        };
        const auto serial=
            simulate_gbm_terminal_prices(config);
        const auto parallel=
            simulate_gbm_terminal_prices_parallel(
                config,
                128
            );
        EXPECT_EQ(serial, parallel);
    }
    TEST(ParallelMonteCarloStressTest, HandlesLargePathCount){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            10'000,
            42u
        };
        const auto prices=
            simulate_gbm_terminal_prices_parallel(
                config,
                8
            );
        EXPECT_EQ(prices.size(), 10'000u);
    }
}