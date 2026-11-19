#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::GbmSimulationConfig;
    using riskforge::simulation::
        simulate_gbm_terminal_prices_parallel;
    TEST(ParallelMonteCarloValidationTest, RejectsZeroWorkerCount){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_gbm_terminal_prices_parallel(
                    config,
                    0
                )
            ),
            std::invalid_argument
        );
    }
    TEST(ParallelMonteCarloValidationTest, RejectsZeroPathCount){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            0,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_gbm_terminal_prices_parallel(
                    config,
                    2
                )
            ),
            std::invalid_argument
        );
    }
    TEST(ParallelMonteCarloValidationTest, RejectsNegativeVolatility){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            -0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_gbm_terminal_prices_parallel(
                    config,
                    2
                )
            ),
            std::invalid_argument
        );
    }
}