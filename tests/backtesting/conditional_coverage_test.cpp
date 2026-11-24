#include "riskforge/backtesting/conditional_coverage.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_conditional_coverage;
    TEST(ConditionalCoverageTest, CalculatesCoverageStatistics){
        const std::vector<double> log_returns{
            0.01,
            -0.03,
            -0.08,
            -0.12,
            0.02
        };
        const auto result=evaluate_conditional_coverage(
            log_returns,
            0.08,
            0.95
        );
        EXPECT_EQ(result.observation_count, 5u);
        EXPECT_EQ(result.exception_count, 1u);
        EXPECT_GE(result.independence_likelihood_ratio, 0.0);
        EXPECT_GE(result.independence_p_value, 0.0);
        EXPECT_LE(result.independence_p_value, 1.0);
        EXPECT_GE(result.conditional_likelihood_ratio, 0.0);
        EXPECT_GE(result.conditional_p_value, 0.0);
        EXPECT_LE(result.conditional_p_value, 1.0);
    }
}