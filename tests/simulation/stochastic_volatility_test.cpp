#include "riskforge/simulation/stochastic_volatility.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::stochastic_volatility_terminal_price;
    TEST(StochasticVolatilityTest, SameSeedAndSampleAreDeterministic){
        const double first=stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, 100u);
        const double second=stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, 100u);
        EXPECT_DOUBLE_EQ(first, second);
    }
    TEST(StochasticVolatilityTest, ZeroVarianceProducesDeterministicGrowth){
        const double result=stochastic_volatility_terminal_price(100.0, 0.05, 0.0, 0.0, 2.0, 0.0, 1.0, 100, 42u, 100u);
        EXPECT_NEAR(result, 105.12710963760242, 1e-12);
    }
    TEST(StochasticVolatilityTest, ProducesPositivePrice){
        const double result=stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, 100u);
        EXPECT_GT(result, 0.0);
    }
}