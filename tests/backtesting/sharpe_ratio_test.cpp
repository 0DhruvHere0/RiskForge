#include "riskforge/backtesting/sharpe_ratio.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::annualized_sharpe_ratio;
    TEST(SharpeRatioTest, CalculatesAnnualizedSharpeRatio){
        const std::vector<double> log_returns{
            0.01,
            0.02,
            0.03
        };
        const double result=annualized_sharpe_ratio(
            log_returns,
            0.005,
            252.0
        );
        EXPECT_NEAR(result, 23.811761799581316, 1e-12);
    }
}