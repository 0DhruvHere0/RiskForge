#include "riskforge/backtesting/stress_grid.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_stress_grid;
    TEST(StressGridValidationTest, RejectsEmptyShockGrid){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        const std::vector<double> additive_shocks;
        EXPECT_THROW(
            static_cast<void>(
                evaluate_stress_grid(
                    log_returns,
                    additive_shocks,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
    TEST(StressGridValidationTest, RejectsNonFiniteShock){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        const std::vector<double> additive_shocks{
            0.0,
            std::numeric_limits<double>::infinity()
        };
        EXPECT_THROW(
            static_cast<void>(
                evaluate_stress_grid(
                    log_returns,
                    additive_shocks,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
}