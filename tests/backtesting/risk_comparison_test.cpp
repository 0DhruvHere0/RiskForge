#include "riskforge/backtesting/risk_comparison.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::backtesting::HistoricalRiskResult;
    using riskforge::backtesting::compare_risk_estimates;
    TEST(RiskComparisonTest, CalculatesRiskDifferences){
        const HistoricalRiskResult historical{
            0.10,
            0.15
        };
        const HistoricalRiskResult simulated{
            0.12,
            0.18
        };
        const auto result=compare_risk_estimates(
            historical,
            simulated
        );
        EXPECT_DOUBLE_EQ(result.value_at_risk_difference, 0.02);
        EXPECT_DOUBLE_EQ(result.expected_shortfall_difference, 0.03);
    }
}