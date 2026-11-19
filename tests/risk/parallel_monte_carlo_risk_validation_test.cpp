#include "riskforge/risk/parallel_monte_carlo_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::risk::estimate_gbm_risk_parallel;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(ParallelMonteCarloRiskValidationTest, RejectsZeroWorkerCount){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            estimate_gbm_risk_parallel(
                config,
                0.95,
                0
            ),
            std::invalid_argument
        );
    }
    TEST(ParallelMonteCarloRiskValidationTest, RejectsInvalidConfidence){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100,
            42u
        };
        EXPECT_THROW(
            estimate_gbm_risk_parallel(
                config,
                1.0,
                2
            ),
            std::invalid_argument
        );
    }
}