#include "riskforge/backtesting/unconditional_coverage.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_unconditional_coverage;
    TEST(UnconditionalCoverageValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(
                evaluate_unconditional_coverage(log_returns, 0.10, 0.95)
            ),
            std::invalid_argument
        );
    }
    TEST(UnconditionalCoverageValidationTest, RejectsInvalidConfidenceLevel){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                evaluate_unconditional_coverage(log_returns, 0.10, 1.0)
            ),
            std::invalid_argument
        );
    }
}