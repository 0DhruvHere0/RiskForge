#include "riskforge/simulation/parallel_stochastic_volatility.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::parallel_stochastic_volatility_terminal_prices;
    TEST(ParallelStochasticVolatilityValidationTest, RejectsZeroPathCount){
        EXPECT_THROW(static_cast<void>(parallel_stochastic_volatility_terminal_prices(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 0, 4, 42u)), std::invalid_argument);
    }
    TEST(ParallelStochasticVolatilityValidationTest, RejectsZeroWorkers){
        EXPECT_THROW(static_cast<void>(parallel_stochastic_volatility_terminal_prices(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 8, 0, 42u)), std::invalid_argument);
    }
}