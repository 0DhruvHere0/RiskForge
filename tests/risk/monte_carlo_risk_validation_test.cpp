#include "riskforge/risk/monte_carlo_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace {
    using riskforge::risk::estimate_gbm_risk;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloRiskValidationTest, RejectsZeroPathCount){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            0,
            42u
        };
        EXPECT_THROW(
            estimate_gbm_risk(config, 0.95),
            std::invalid_argument
        );
    }
    TEST(MonteCarloRiskValidationTest, RejectsConfidenceLevelOfZero){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            estimate_gbm_risk(config, 0.0),
            std::invalid_argument
        );
    }
    TEST(MonteCarloRiskValidationTest, RejectsConfidenceLevelOfOne){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            estimate_gbm_risk(config, 1.0),
            std::invalid_argument
        );
    }
}