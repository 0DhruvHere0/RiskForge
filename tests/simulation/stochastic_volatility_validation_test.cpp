#include "riskforge/simulation/stochastic_volatility.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::stochastic_volatility_terminal_price;
    TEST(StochasticVolatilityValidationTest, RejectsZeroSteps){
        EXPECT_THROW(static_cast<void>(stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 0, 42u, 100u)), std::invalid_argument);
    }
    TEST(StochasticVolatilityValidationTest, RejectsNegativeVariance){
        EXPECT_THROW(static_cast<void>(stochastic_volatility_terminal_price(100.0, 0.05, -0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, 100u)), std::invalid_argument);
    }
    TEST(StochasticVolatilityValidationTest, RejectsNonPositiveMeanReversion){
        EXPECT_THROW(static_cast<void>(stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 0.0, 0.10, 1.0, 100, 42u, 100u)), std::invalid_argument);
    }
}