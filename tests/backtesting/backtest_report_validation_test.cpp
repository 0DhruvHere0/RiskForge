#include "riskforge/backtesting/backtest_report.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::create_backtest_report;
    TEST(BacktestReportValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(
                create_backtest_report(log_returns, 0.10, 252.0)
            ),
            std::invalid_argument
        );
    }
    TEST(BacktestReportValidationTest, RejectsInvalidPeriodsPerYear){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                create_backtest_report(log_returns, 0.10, 0.0)
            ),
            std::invalid_argument
        );
    }
}