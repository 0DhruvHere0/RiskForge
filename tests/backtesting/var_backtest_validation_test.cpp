#include "riskforge/backtesting/var_backtest.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::backtest_value_at_risk;
    TEST(VarBacktestValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(static_cast<void>(backtest_value_at_risk(log_returns, 0.10)), std::invalid_argument);
    }
    TEST(VarBacktestValidationTest, RejectsNonFiniteThreshold){
        const std::vector<double> log_returns{
            -0.02,
            -0.03
        };
        EXPECT_THROW(static_cast<void>(backtest_value_at_risk(log_returns, std::numeric_limits<double>::infinity())), std::invalid_argument);
    }
    TEST(VarBacktestValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            -0.02,
            std::numeric_limits<double>::quiet_NaN()
        };
        EXPECT_THROW(static_cast<void>(backtest_value_at_risk(log_returns, 0.10)), std::invalid_argument);
    }
}