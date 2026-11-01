#include "riskforge/random/normal.hpp"
#include <cmath>
#include <gtest/gtest.h>
namespace{
    using riskforge::random::normal_ppf;
    TEST(NormalTest, MedianIsZero){
        EXPECT_NEAR(normal_ppf(0.5), 0.0, 1e-15);
    }
    TEST(NormalTest, MatchesReferenceQuantiles)
    {
        EXPECT_NEAR(normal_ppf(0.025), -1.959963984540054, 1e-8);
        EXPECT_NEAR(normal_ppf(0.975), 1.959963984540054, 1e-8);
        EXPECT_NEAR(normal_ppf(0.001), -3.090232306167813, 1e-8);
        EXPECT_NEAR(normal_ppf(0.999), 3.090232306167813, 1e-8);
        EXPECT_NEAR(normal_ppf(0.0000005), -4.891638475698592, 1e-8);
        EXPECT_NEAR(normal_ppf(0.9999995), 4.891638475698592, 1e-8);
    }
    TEST(NormalTest, IsAntisymmetric){
        EXPECT_NEAR(normal_ppf(0.025), -normal_ppf(0.975), 1e-12);
        EXPECT_NEAR(normal_ppf(0.001), -normal_ppf(0.999), 1e-12);
    }
    TEST(NormalTest, HandlesProbabilityBoundaries){
        EXPECT_TRUE(std::isinf(normal_ppf(0.0)));
        EXPECT_TRUE(normal_ppf(0.0)<0.0);
        EXPECT_TRUE(std::isinf(normal_ppf(1.0)));
        EXPECT_TRUE(normal_ppf(1.0)>0.0);
    }
}