#include "riskforge/risk/monte_carlo_risk.hpp"
#include "riskforge/risk/parallel_monte_carlo_risk.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::risk::estimate_gbm_risk;
    using riskforge::risk::estimate_gbm_risk_parallel;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(ParallelMonteCarloRiskTest, MatchesSerialRiskEstimation){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            2000,
            42u
        };
        const auto serial=
            estimate_gbm_risk(config, 0.95);
        const auto parallel=
            estimate_gbm_risk_parallel(
                config,
                0.95,
                4
            );
        EXPECT_DOUBLE_EQ(
            serial.value_at_risk,
            parallel.value_at_risk
        );
        EXPECT_DOUBLE_EQ(
            serial.expected_shortfall,
            parallel.expected_shortfall
        );
    }
    TEST(ParallelMonteCarloRiskTest, IsDeterministicAcrossWorkerCounts){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            2000,
            42u
        };
        const auto two_workers=
            estimate_gbm_risk_parallel(
                config,
                0.95,
                2
            );
        const auto four_workers=
            estimate_gbm_risk_parallel(
                config,
                0.95,
                4
            );
        EXPECT_DOUBLE_EQ(
            two_workers.value_at_risk,
            four_workers.value_at_risk
        );
        EXPECT_DOUBLE_EQ(
            two_workers.expected_shortfall,
            four_workers.expected_shortfall
        );
    }
}