#include "riskforge/backtesting/rolling_backtest.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::rolling_backtest_reports;
    TEST(RollingBacktestValidationTest, RejectsWindowSmallerThanTwo){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                rolling_backtest_reports(
                    log_returns,
                    1u,
                    0.08,
                    252.0
                )
            ),
            std::invalid_argument
        );
    }
    TEST(RollingBacktestValidationTest, RejectsWindowLargerThanInput){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                rolling_backtest_reports(
                    log_returns,
                    3u,
                    0.08,
                    252.0
                )
            ),
            std::invalid_argument
        );
    }
}