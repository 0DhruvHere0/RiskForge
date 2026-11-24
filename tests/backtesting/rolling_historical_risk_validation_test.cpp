#include "riskforge/backtesting/rolling_historical_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::rolling_historical_risk;
    TEST(RollingHistoricalRiskValidationTest, RejectsWindowSmallerThanTwo){
        const std::vector<double> log_returns{
            -0.01,
            -0.02
        };
        EXPECT_THROW(static_cast<void>(rolling_historical_risk(log_returns, 1u, 0.95)), std::invalid_argument);
    }
    TEST(RollingHistoricalRiskValidationTest, RejectsWindowLargerThanInput){
        const std::vector<double> log_returns{
            -0.01,
            -0.02
        };
        EXPECT_THROW(static_cast<void>(rolling_historical_risk(log_returns, 3u, 0.95)), std::invalid_argument);
    }
}