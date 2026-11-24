#include "riskforge/backtesting/historical_volatility.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::annualized_historical_volatility;
    TEST(HistoricalVolatilityValidationTest, RejectsTooFewReturns){
        const std::vector<double> log_returns{0.01};
        EXPECT_THROW(
            static_cast<void>(
                annualized_historical_volatility(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
    TEST(HistoricalVolatilityValidationTest, RejectsInvalidPeriodsPerYear){
        const std::vector<double> log_returns{
            0.01,
            0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                annualized_historical_volatility(log_returns, 0.0)
            ),
            std::invalid_argument
        );
    }
    TEST(HistoricalVolatilityValidationTest, RejectsNonFiniteReturn){
        const std::vector<double> log_returns{
            0.01,
            std::numeric_limits<double>::quiet_NaN()
        };
        EXPECT_THROW(
            static_cast<void>(
                annualized_historical_volatility(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
}