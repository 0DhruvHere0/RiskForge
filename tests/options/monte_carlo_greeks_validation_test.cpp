#include "riskforge/options/monte_carlo_greeks.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::monte_carlo_call_delta;
    using riskforge::options::monte_carlo_call_vega;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloGreeksValidationTest, RejectsZeroSpotBump){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 100, 42u};
        EXPECT_THROW(static_cast<void>(monte_carlo_call_delta(config, 100.0, 0.05, 2, 0.0)), std::invalid_argument);
    }
    TEST(MonteCarloGreeksValidationTest, RejectsZeroVolatilityBump){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 100, 42u};
        EXPECT_THROW(static_cast<void>(monte_carlo_call_vega(config, 100.0, 0.05, 2, 0.0)), std::invalid_argument);
    }
    TEST(MonteCarloGreeksValidationTest, RejectsZeroWorkers){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 100, 42u};
        EXPECT_THROW(static_cast<void>(monte_carlo_call_delta(config, 100.0, 0.05, 0, 0.01)), std::invalid_argument);
    }
}