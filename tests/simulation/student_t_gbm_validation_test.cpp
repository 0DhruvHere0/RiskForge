#include "riskforge/simulation/student_t_gbm.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::student_t_gbm_terminal_price;
    TEST(StudentTGbmValidationTest, RejectsInvalidDegreesOfFreedom){
        EXPECT_THROW(static_cast<void>(student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 2.0, 42u, 100u)), std::invalid_argument);
    }
    TEST(StudentTGbmValidationTest, RejectsNonPositiveInitialPrice){
        EXPECT_THROW(static_cast<void>(student_t_gbm_terminal_price(0.0, 0.05, 0.20, 1.0, 8.0, 42u, 100u)), std::invalid_argument);
    }
    TEST(StudentTGbmValidationTest, RejectsNegativeVolatility){
        EXPECT_THROW(static_cast<void>(student_t_gbm_terminal_price(100.0, 0.05, -0.20, 1.0, 8.0, 42u, 100u)), std::invalid_argument);
    }
}