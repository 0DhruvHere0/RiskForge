#include "riskforge/backtesting/stress_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::estimate_stressed_risk;
    TEST(StressRiskValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(
                estimate_stressed_risk(log_returns, -0.03, 0.95)
            ),
            std::invalid_argument
        );
    }
    TEST(StressRiskValidationTest, RejectsInvalidConfidenceLevel){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                estimate_stressed_risk(log_returns, -0.03, 1.0)
            ),
            std::invalid_argument
        );
    }
}