#include "riskforge/risk/expected_shortfall.hpp"
#include "riskforge/risk/var.hpp"
#include <cmath>
#include <gtest/gtest.h>
namespace{
    using riskforge::risk::lognormal_expected_shortfall;
    using riskforge::risk::lognormal_value_at_risk;
    TEST(ExpectedShortfallTest, ZeroVolatilityMatchesDeterministicLoss){
        const double result= lognormal_expected_shortfall(100.0, 0.05, 0.0, 1.0, 0.95);
        const double expected= 100.0- 100.0*std::exp(0.05);
        EXPECT_NEAR(result, expected, 1e-12);
    }
    TEST(ExpectedShortfallTest, ExceedsValueAtRiskForPositiveVolatility){
        const double value_at_risk= lognormal_value_at_risk(100.0, 0.05, 0.2, 1.0, 0.95);
        const double expected_shortfall= lognormal_expected_shortfall(100.0, 0.05, 0.2, 1.0, 0.95);
        EXPECT_TRUE(std::isfinite(expected_shortfall));
        EXPECT_GT(expected_shortfall, value_at_risk);
    }
    TEST(ExpectedShortfallTest, RejectsInvalidConfidenceLevel){
        EXPECT_THROW(
            lognormal_expected_shortfall(100.0, 0.05, 0.2, 1.0, 0.0),
            std::invalid_argument
        );
    }
}