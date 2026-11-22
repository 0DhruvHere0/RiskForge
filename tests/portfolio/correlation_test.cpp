#include "riskforge/portfolio/correlation.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::portfolio::Matrix;
    using riskforge::portfolio::cholesky_decompose;
    TEST(CorrelationTest, DecomposesTwoByTwoMatrix){
        const Matrix correlation{
            {1.0, 0.5},
            {0.5, 1.0}
        };
        const Matrix lower= cholesky_decompose(correlation);
        ASSERT_EQ(lower.size(), 2u);
        ASSERT_EQ(lower[0].size(), 2u);
        EXPECT_NEAR(lower[0][0], 1.0, 1e-12);
        EXPECT_NEAR(lower[0][1], 0.0, 1e-12);
        EXPECT_NEAR(lower[1][0], 0.5, 1e-12);
        EXPECT_NEAR(
            lower[1][1],
            std::sqrt(0.75),
            1e-12
        );
    }
    TEST(CorrelationTest, DecomposesIdentityMatrix){
        const Matrix correlation{
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0}
        };
        const Matrix lower= cholesky_decompose(correlation);
        EXPECT_EQ(lower, correlation);
    }
}