#include "riskforge/backtesting/historical_volatility.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::annualized_historical_volatility;
    TEST(HistoricalVolatilityTest, CalculatesAnnualizedSampleVolatility){
        const std::vector<double> log_returns{
            0.01,
            0.02,
            0.03
        };
        const double result=annualized_historical_volatility(
            log_returns,
            252.0
        );
        EXPECT_NEAR(result, 0.15874507866387544, 1e-12);
    }
    TEST(HistoricalVolatilityTest, ConstantReturnsHaveZeroVolatility){
        const std::vector<double> log_returns{
            0.02,
            0.02,
            0.02
        };
        EXPECT_DOUBLE_EQ(
            annualized_historical_volatility(log_returns, 252.0),
            0.0
        );
    }
}