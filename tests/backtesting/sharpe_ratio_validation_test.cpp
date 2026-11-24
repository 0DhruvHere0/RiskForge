#include "riskforge/backtesting/sharpe_ratio.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::annualized_sharpe_ratio;
    TEST(SharpeRatioValidationTest, RejectsTooFewReturns){
        const std::vector<double> log_returns{0.01};
        EXPECT_THROW(
            static_cast<void>(
                annualized_sharpe_ratio(log_returns, 0.0, 252.0)
            ),
            std::invalid_argument
        );
    }
    TEST(SharpeRatioValidationTest, RejectsZeroPeriodsPerYear){
        const std::vector<double> log_returns{
            0.01,
            0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                annualized_sharpe_ratio(log_returns, 0.0, 0.0)
            ),
            std::invalid_argument
        );
    }
    TEST(SharpeRatioValidationTest, RejectsZeroVolatility){
        const std::vector<double> log_returns{
            0.02,
            0.02,
            0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                annualized_sharpe_ratio(log_returns, 0.0, 252.0)
            ),
            std::domain_error
        );
    }
}