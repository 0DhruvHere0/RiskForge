#include "riskforge/simulation/gbm.hpp"
#include <cmath>
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::gbm_terminal_price;
    TEST(GBMTest, ZeroDriftZeroVolatilityPreservePrice){
        const double result= gbm_terminal_price(100.0, 0.0, 0.0, 1.0, 0.0);
        EXPECT_DOUBLE_EQ(result, 100.0);
    }
    TEST(GBMTest, AppliesDeterministicGrowth){
        const double result= gbm_terminal_price(100.0, 0.05, 0.0, 1.0, 0.0);
        EXPECT_NEAR(result, 105.12710963760242, 1e-12);
    }
    TEST(GBMTest, AppliesDiffusionTerm){
        const double result= gbm_terminal_price(100.0, 0.05, 0.2, 1.0, 1.0);
        EXPECT_NEAR(result, 125.86000099294779, 1e-12);
    }
}