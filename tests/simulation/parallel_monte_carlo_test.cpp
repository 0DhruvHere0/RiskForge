#include "riskforge/simulation/monte_carlo.hpp"
#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::GbmSimulationConfig;
    using riskforge::simulation::
        simulate_gbm_terminal_prices;
    using riskforge::simulation::
        simulate_gbm_terminal_prices_parallel;
    TEST(ParallelMonteCarloTest, MatchesSerialSimulation){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            256,
            42u
        };
        const auto serial=
            simulate_gbm_terminal_prices(config);
        const auto parallel=
            simulate_gbm_terminal_prices_parallel(
                config,
                4
            );
        EXPECT_EQ(serial, parallel);
    }
    TEST(ParallelMonteCarloTest, IsDeterministicAcrossWorkerCounts){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            256,
            42u
        };
        const auto two_workers=
            simulate_gbm_terminal_prices_parallel(
                config,
                2
            );
        const auto four_workers=
            simulate_gbm_terminal_prices_parallel(
                config,
                4
            );
        EXPECT_EQ(two_workers, four_workers);
    }
    TEST(ParallelMonteCarloTest, ProducesRequestedNumberOfPaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        const auto prices=
            simulate_gbm_terminal_prices_parallel(
                config,
                3
            );
        EXPECT_EQ(prices.size(), 100u);
    }
}