#include "riskforge/backtesting/drawdown.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
namespace{
    using riskforge::backtesting::maximum_drawdown;
    TEST(DrawdownTest, CalculatesMaximumDrawdown){
        const std::vector<double> log_returns{
            std::log(1.10),
            std::log(0.95),
            std::log(0.80),
            std::log(1.10)
        };
        EXPECT_NEAR(
            maximum_drawdown(log_returns),
            0.24,
            1e-12
        );
    }
    TEST(DrawdownTest, NonNegativeReturnsHaveZeroDrawdown){
        const std::vector<double> log_returns{
            0.01,
            0.02,
            0.03
        };
        EXPECT_DOUBLE_EQ(maximum_drawdown(log_returns), 0.0);
    }
}