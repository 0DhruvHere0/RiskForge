#include "riskforge/risk/var.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::risk::lognormal_value_at_risk;
    TEST(ValueAtRiskTest, ZeroVolatilityMatchesDeterministicLoss){
        const double result= lognormal_value_at_risk(100.0, 0.05, 0.0, 1.0, 0.95);
        const double expected= 100.0- 100.0* std::exp(0.05);
        EXPECT_NEAR(result, expected, 1e-12);
    }
    TEST(ValueAtRiskTest, PositiveVolatilityProducesFiniteLoss){
        const double result= lognormal_value_at_risk(100.0, 0.05, 0.2, 1.0, 0.95);
        EXPECT_TRUE(std::isfinite(result));
        EXPECT_GT(result, 0.0);
    }
    TEST(ValueAtRiskTest, RejectsInvalidConfidenceLevel){
        EXPECT_THROW(
            static_cast<void>(
                lognormal_value_at_risk(100.0, 0.05, 0.2, 1.0, 1.0)
            ),
            std::invalid_argument
        );
    }
}