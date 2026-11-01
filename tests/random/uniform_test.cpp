#include "riskforge/random/uniform.hpp"
#include <cmath>
#include <gtest/gtest.h>
namespace{
    using riskforge::random::uniform_open01;
    TEST(UniformTest, MinimumInputProducesValueAboveZero){
        const double value= uniform_open01(0x00000000u, 0x00000000u);
        EXPECT_GT(value, 0.0);
        EXPECT_LT(value, 1.0);
    }
    TEST(UniformTest, MaximumInputProducesValueBelowOne){
        const double value= uniform_open01(0xFFFFFFFFu, 0xFFFFFFFFu);
        EXPECT_GT(value, 0.0);
        EXPECT_LT(value, 1.0);
        EXPECT_DOUBLE_EQ(value, std::nextafter(1.0, 0.0));
    }
    TEST(UniformTest, SameInputProducesSameValue){
        const double first= uniform_open01(0x12345678u, 0x9ABCDEF0u);
        const double second= uniform_open01(0x12345678u, 0x9ABCDEF0u);
        EXPECT_DOUBLE_EQ(first, second);
        EXPECT_GT(first, 0.0);
        EXPECT_LT(second, 1.0);
    }
}