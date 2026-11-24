#include "riskforge/backtesting/stress_grid.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_stress_grid;
    TEST(StressGridTest, EvaluatesMultipleStressScenarios){
        const std::vector<double> log_returns{
            0.01,
            -0.02,
            -0.08,
            -0.12,
            0.02
        };
        const std::vector<double> additive_shocks{
            -0.03,
            0.0,
            0.03
        };
        const auto results=evaluate_stress_grid(
            log_returns,
            additive_shocks,
            0.80
        );
        ASSERT_EQ(results.size(), 3u);
        EXPECT_GT(
            results[0].value_at_risk,
            results[1].value_at_risk
        );
        EXPECT_GT(
            results[1].value_at_risk,
            results[2].value_at_risk
        );
    }
}