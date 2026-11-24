#include "riskforge/backtesting/historical_risk.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::estimate_historical_risk;
    TEST(HistoricalRiskTest, CalculatesHistoricalRisk){
        const std::vector<double> log_returns{
            0.10,
            0.05,
            -0.02,
            -0.08,
            -0.15
        };
        const auto result=estimate_historical_risk(log_returns, 0.80);
        EXPECT_DOUBLE_EQ(result.value_at_risk, 0.08);
        EXPECT_DOUBLE_EQ(result.expected_shortfall, 0.115);
    }
    TEST(HistoricalRiskTest, ExpectedShortfallIsAtLeastValueAtRisk){
        const std::vector<double> log_returns{
            0.02,
            -0.01,
            -0.04,
            -0.09
        };
        const auto result=estimate_historical_risk(log_returns, 0.75);
        EXPECT_GE(result.expected_shortfall, result.value_at_risk);
    }
}