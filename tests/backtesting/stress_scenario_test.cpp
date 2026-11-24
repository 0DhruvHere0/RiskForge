#include "riskforge/backtesting/stress_scenario.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::apply_return_shock;
    TEST(StressScenarioTest, AppliesAdditiveReturnShock){
        const std::vector<double> log_returns{
            0.01,
            -0.02,
            0.03
        };
        const auto stressed_returns=apply_return_shock(
            log_returns,
            -0.05
        );
        ASSERT_EQ(stressed_returns.size(), 3u);
        EXPECT_DOUBLE_EQ(stressed_returns[0], -0.04);
        EXPECT_DOUBLE_EQ(stressed_returns[1], -0.07);
        EXPECT_DOUBLE_EQ(stressed_returns[2], -0.02);
    }
}