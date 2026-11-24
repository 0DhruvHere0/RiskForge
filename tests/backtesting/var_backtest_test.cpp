#include "riskforge/backtesting/var_backtest.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::backtest_value_at_risk;
    TEST(VarBacktestTest, CountsVaRExceptions){
        const std::vector<double> log_returns{
            0.02,
            -0.03,
            -0.08,
            -0.12,
            0.01
        };
        const auto result=backtest_value_at_risk(log_returns, 0.08);
        EXPECT_EQ(result.observation_count, 5u);
        EXPECT_EQ(result.exception_count, 1u);
        EXPECT_DOUBLE_EQ(result.exception_rate, 0.2);
    }
    TEST(VarBacktestTest, DoesNotCountBoundaryAsException){
        const std::vector<double> log_returns{
            -0.05,
            -0.10
        };
        const auto result=backtest_value_at_risk(log_returns, 0.10);
        EXPECT_EQ(result.exception_count, 0u);
        EXPECT_DOUBLE_EQ(result.exception_rate, 0.0);
    }
}