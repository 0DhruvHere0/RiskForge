#include "riskforge/backtesting/unconditional_coverage.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_unconditional_coverage;
    TEST(UnconditionalCoverageTest, CalculatesCoverageStatistics){
        const std::vector<double> log_returns{
            0.01,
            -0.03,
            -0.08,
            -0.12,
            0.02
        };
        const auto result=evaluate_unconditional_coverage(
            log_returns,
            0.08,
            0.95
        );
        EXPECT_EQ(result.observation_count, 5u);
        EXPECT_EQ(result.exception_count, 1u);
        EXPECT_DOUBLE_EQ(result.observed_exception_rate, 0.2);
        EXPECT_NEAR(result.expected_exception_rate, 0.05, 1e-12);
        EXPECT_GE(result.likelihood_ratio, 0.0);
        EXPECT_GE(result.p_value, 0.0);
        EXPECT_LE(result.p_value, 1.0);
    }
}