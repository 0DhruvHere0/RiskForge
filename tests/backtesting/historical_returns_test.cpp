#include "riskforge/backtesting/historical_returns.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::historical_log_returns;
    TEST(HistoricalReturnsTest, CalculatesLogReturns){
        const std::vector<double> prices{
            100.0,
            110.0,
            99.0
        };
        const auto returns=historical_log_returns(prices);
        ASSERT_EQ(returns.size(), 2u);
        EXPECT_NEAR(returns[0], 0.0953101798043249, 1e-12);
        EXPECT_NEAR(returns[1], -0.1053605156578263, 1e-12);
    }
    TEST(HistoricalReturnsTest, RejectsTooFewPrices){
        const std::vector<double> prices{100.0};
        EXPECT_THROW(static_cast<void>(historical_log_returns(prices)), std::invalid_argument);
    }
    TEST(HistoricalReturnsTest, RejectsNonPositivePrices){
        const std::vector<double> prices{
            100.0,
            0.0
        };
        EXPECT_THROW(static_cast<void>(historical_log_returns(prices)), std::invalid_argument);
    }
}