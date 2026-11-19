#include "riskforge/risk/parallel_monte_carlo_risk.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::risk::
        estimate_gbm_risk_parallel;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(ParallelMonteCarloRiskStressTest, HandlesLargeRiskEstimate){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            10'000,
            42u
        };
        const auto result=
            estimate_gbm_risk_parallel(
                config,
                0.95,
                8
            );
        EXPECT_TRUE(
            std::isfinite(result.value_at_risk)
        );
        EXPECT_TRUE(
            std::isfinite(result.expected_shortfall)
        );
        EXPECT_GE(
            result.expected_shortfall,
            result.value_at_risk
        );
    }
    TEST(ParallelMonteCarloRiskStressTest, HandlesMoreWorkersThanPaths){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            32,
            42u
        };
        const auto result=
            estimate_gbm_risk_parallel(
                config,
                0.95,
                128
            );
        EXPECT_TRUE(
            std::isfinite(result.value_at_risk)
        );
        EXPECT_TRUE(
            std::isfinite(result.expected_shortfall)
        );
    }
}