#include "riskforge/random/student_t.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::random::student_t_sample;
    TEST(StudentTValidationTest, RejectsZeroDegreesOfFreedom){
        EXPECT_THROW(static_cast<void>(student_t_sample(0.0, 42u, 0u)), std::invalid_argument);
    }
    TEST(StudentTValidationTest, RejectsNegativeDegreesOfFreedom){
        EXPECT_THROW(static_cast<void>(student_t_sample(-2.0, 42u, 0u)), std::invalid_argument);
    }
}