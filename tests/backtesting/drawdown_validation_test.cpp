#include "riskforge/backtesting/drawdown.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::maximum_drawdown;
    TEST(DrawdownValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(maximum_drawdown(log_returns)),
            std::invalid_argument
        );
    }
    TEST(DrawdownValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            0.01,
            std::numeric_limits<double>::infinity()
        };
        EXPECT_THROW(
            static_cast<void>(maximum_drawdown(log_returns)),
            std::invalid_argument
        );
    }
}