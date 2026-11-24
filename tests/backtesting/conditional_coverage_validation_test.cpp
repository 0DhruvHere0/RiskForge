#include "riskforge/backtesting/conditional_coverage.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::evaluate_conditional_coverage;
    TEST(ConditionalCoverageValidationTest, RejectsTooFewReturns){
        const std::vector<double> log_returns{0.01};
        EXPECT_THROW(
            static_cast<void>(
                evaluate_conditional_coverage(log_returns, 0.10, 0.95)
            ),
            std::invalid_argument
        );
    }
    TEST(ConditionalCoverageValidationTest, RejectsInvalidConfidenceLevel){
        const std::vector<double> log_returns{
            0.01,
            -0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                evaluate_conditional_coverage(log_returns, 0.10, 1.0)
            ),
            std::invalid_argument
        );
    }
}