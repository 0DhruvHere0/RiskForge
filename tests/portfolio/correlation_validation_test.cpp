#include "riskforge/portfolio/correlation.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::cholesky_decompose;
    TEST(CorrelationValidationTest, RejectsEmptyMatrix){
        const Matrix correlation;
        EXPECT_THROW(
            static_cast<void>(cholesky_decompose(correlation)),
            std::invalid_argument
        );
    }
    TEST(CorrelationValidationTest, RejectsNonSquareMatrix){
        const Matrix correlation{
            {1.0, 0.0},
            {0.0}
        };
        EXPECT_THROW(
            static_cast<void>(cholesky_decompose(correlation)),
            std::invalid_argument
        );
    }
    TEST(CorrelationValidationTest, RejectsNonSymmetricMatrix){
        const Matrix correlation{
            {1.0, 0.2},
            {0.5, 1.0}
        };
        EXPECT_THROW(
            static_cast<void>(cholesky_decompose(correlation)),
            std::invalid_argument
        );
    }
    TEST(CorrelationValidationTest, RejectsNonPositiveDefiniteMatrix){
        const Matrix correlation{
            {1.0, 2.0},
            {2.0, 1.0}
        };
        EXPECT_THROW(
            static_cast<void>(cholesky_decompose(correlation)),
            std::invalid_argument
        );
    }
}