#include "riskforge/backtesting/stress_risk.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::estimate_stressed_risk;
    TEST(StressRiskTest, CalculatesRiskAfterReturnShock){
        const std::vector<double> log_returns{
            0.01,
            -0.02,
            -0.08,
            -0.12,
            0.02
        };
        const auto result=estimate_stressed_risk(
            log_returns,
            -0.03,
            0.80
        );
        EXPECT_DOUBLE_EQ(result.value_at_risk, 0.11);
        EXPECT_DOUBLE_EQ(result.expected_shortfall, 0.13);
    }
}