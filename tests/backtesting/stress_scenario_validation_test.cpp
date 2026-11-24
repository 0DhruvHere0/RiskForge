#include "riskforge/backtesting/stress_scenario.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::apply_return_shock;
    TEST(StressScenarioValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(
                apply_return_shock(log_returns, -0.05)
            ),
            std::invalid_argument
        );
    }
    TEST(StressScenarioValidationTest, RejectsNonFiniteShock){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                apply_return_shock(
                    log_returns,
                    std::numeric_limits<double>::infinity()
                )
            ),
            std::invalid_argument
        );
    }
    TEST(StressScenarioValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            0.01,
            std::numeric_limits<double>::quiet_NaN()
        };
        EXPECT_THROW(
            static_cast<void>(
                apply_return_shock(log_returns, -0.05)
            ),
            std::invalid_argument
        );
    }
}