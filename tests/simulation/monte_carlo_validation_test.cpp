#include "riskforge/simulation/monte_carlo.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::GbmSimulationConfig;
    using riskforge::simulation::simulate_gbm_terminal_prices;
    TEST(MonteCarloValidationTest, RejectsNonPositiveInitialPrice){
        const GbmSimulationConfig config{
            0.0,
            0.05,
            0.20,
            1.0,
            10,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
    TEST(MonteCarloValidationTest, RejectsNegativeVolatility){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            -0.20,
            1.0,
            10,
            42u
        };
        EXPECT_THROW(
            static_cast<void>(
                simulate_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
    TEST(MonteCarloValidationTest, RejectsZeroPathCount){
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
                simulate_gbm_terminal_prices(config)
            ),
            std::invalid_argument
        );
    }
}