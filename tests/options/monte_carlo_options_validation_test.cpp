#include "riskforge/options/monte_carlo_options.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>
namespace{
    using riskforge::options::monte_carlo_european_call_price;
    using riskforge::options::monte_carlo_european_put_price;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloOptionsValidationTest, RejectsNonPositiveStrike){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(static_cast<void>(monte_carlo_european_call_price(config, 0.0, 0.05, 2)), std::invalid_argument);
    }
    TEST(MonteCarloOptionsValidationTest, RejectsZeroWorkers){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(static_cast<void>(monte_carlo_european_put_price(config, 100.0, 0.05, 0)), std::invalid_argument);
    }
    TEST(MonteCarloOptionsValidationTest, RejectsNonFiniteRate){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(static_cast<void>(monte_carlo_european_call_price(config, 100.0, std::numeric_limits<double>::infinity(), 2)), std::invalid_argument);
    }
}