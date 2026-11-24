#include "riskforge/backtesting/rolling_historical_risk.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::rolling_historical_risk;
    TEST(RollingHistoricalRiskTest, CalculatesRollingRisk){
        const std::vector<double> log_returns{
            -0.01,
            -0.02,
            -0.08,
            -0.04,
            -0.12
        };
        const auto results=rolling_historical_risk(log_returns, 3, 2.0/3.0);
        ASSERT_EQ(results.size(), 3u);
        EXPECT_DOUBLE_EQ(results[0].value_at_risk, 0.02);
        EXPECT_DOUBLE_EQ(results[1].value_at_risk, 0.04);
        EXPECT_DOUBLE_EQ(results[2].value_at_risk, 0.08);
        EXPECT_DOUBLE_EQ(results[0].expected_shortfall, 0.05);
        EXPECT_DOUBLE_EQ(results[1].expected_shortfall, 0.06);
        EXPECT_DOUBLE_EQ(results[2].expected_shortfall, 0.10);
    }
}