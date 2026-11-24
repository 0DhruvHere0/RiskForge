#include "riskforge/random/student_t.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <cstdint>
namespace{
    using riskforge::random::student_t_sample;
    TEST(StudentTTest, SameSeedAndSampleAreDeterministic){
        const double first=student_t_sample(8.0, 42u, 100u);
        const double second=student_t_sample(8.0, 42u, 100u);
        EXPECT_DOUBLE_EQ(first, second);
    }
    TEST(StudentTTest, DifferentSamplesProduceDifferentValues){
        const double first=student_t_sample(8.0, 42u, 100u);
        const double second=student_t_sample(8.0, 42u, 101u);
        EXPECT_NE(first, second);
    }
    TEST(StudentTTest, ProducesFiniteValues){
        for (std::uint64_t sample=0; sample<100; ++sample){
            EXPECT_TRUE(std::isfinite(student_t_sample(5.0, 42u, sample)));
        }
    }
}