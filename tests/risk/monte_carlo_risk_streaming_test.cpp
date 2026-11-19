#include "riskforge/risk/monte_carlo_risk.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::risk::estimate_gbm_risk;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloRiskStreamingTest, HandlesSinglePath){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.0,
            1.0,
            1,
            42u
        };
        const auto result= estimate_gbm_risk(config, 0.95);
        EXPECT_NEAR(
            result.value_at_risk,
            -5.12710963760242,
            1e-12
        );
        EXPECT_NEAR(
            result.expected_shortfall,
            -5.12710963760242,
            1e-12
        );
    }
    TEST(MonteCarloRiskStreamingTest, IsDeterministic){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            2000,
            42u
        };
        const auto first= estimate_gbm_risk(config, 0.95);
        const auto second= estimate_gbm_risk(config, 0.95);
        EXPECT_DOUBLE_EQ(
            first.value_at_risk,
            second.value_at_risk
        );
        EXPECT_DOUBLE_EQ(
            first.expected_shortfall,
            second.expected_shortfall
        );
    }
}