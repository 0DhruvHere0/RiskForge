#include "riskforge/backtesting/historical_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include <limits>
namespace{
    using riskforge::backtesting::estimate_historical_risk;
    TEST(HistoricalRiskValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(static_cast<void>(estimate_historical_risk(log_returns, 0.95)), std::invalid_argument);
    }
    TEST(HistoricalRiskValidationTest, RejectsInvalidConfidenceLevel){
        const std::vector<double> log_returns{
            -0.01,
            -0.02
        };
        EXPECT_THROW(static_cast<void>(estimate_historical_risk(log_returns, 1.0)), std::invalid_argument);
    }
    TEST(HistoricalRiskValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            -0.01,
            std::numeric_limits<double>::quiet_NaN()
        };
        EXPECT_THROW(static_cast<void>(estimate_historical_risk(log_returns, 0.95)), std::invalid_argument);
    }
}