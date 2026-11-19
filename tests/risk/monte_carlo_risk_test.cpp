#include "riskforge/risk/monte_carlo_risk.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::risk::estimate_gbm_risk;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloRiskTest, ProducesFiniteRiskMeasures){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            10'000,
            42u
        };
        const auto result= estimate_gbm_risk(config, 0.95);
        EXPECT_TRUE(std::isfinite(result.value_at_risk));
        EXPECT_TRUE(std::isfinite(result.expected_shortfall));
    }
    TEST(MonteCarloRiskTest, ExpectedShortfallIsAtLeastValueAtRisk){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            10'000,
            42u
        };
        const auto result= estimate_gbm_risk(config, 0.95);
        EXPECT_GE(
            result.expected_shortfall,
            result.value_at_risk
        );
    }
    TEST(MonteCarloRiskTest, SameSeedProducesSameRiskMeasures){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            2'000,
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