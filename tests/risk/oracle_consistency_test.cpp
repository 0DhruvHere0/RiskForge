#include "riskforge/risk/expected_shortfall.hpp"
#include "riskforge/risk/var.hpp"
#include <gtest/gtest.h>
namespace {
using riskforge::risk::lognormal_expected_shortfall;
using riskforge::risk::lognormal_value_at_risk;
TEST(OracleConsistencyTest, ExpectedShortfallIsAtLeastValueAtRisk) {
    const double value_at_risk =lognormal_value_at_risk(100.0, 0.05, 0.2, 1.0, 0.95);
    const double expected_shortfall =lognormal_expected_shortfall(100.0, 0.05, 0.2, 1.0, 0.95);
    EXPECT_GE(expected_shortfall, value_at_risk);
}
TEST(OracleConsistencyTest, ZeroVolatilityOraclesAgree) {
    const double value_at_risk =lognormal_value_at_risk(100.0, 0.05, 0.0, 1.0, 0.95);
    const double expected_shortfall =lognormal_expected_shortfall(100.0, 0.05, 0.0, 1.0, 0.95);
    EXPECT_NEAR(expected_shortfall, value_at_risk, 1e-12);
   }
}