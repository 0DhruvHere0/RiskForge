#include "riskforge/simulation/student_t_gbm.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::student_t_gbm_terminal_price;
    TEST(StudentTGbmTest, SameSeedAndSampleAreDeterministic){
        const double first=student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 8.0, 42u, 100u);
        const double second=student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 8.0, 42u, 100u);
        EXPECT_DOUBLE_EQ(first, second);
    }
    TEST(StudentTGbmTest, ZeroVolatilityProducesDeterministicGrowth){
        const double result=student_t_gbm_terminal_price(100.0, 0.05, 0.0, 1.0, 8.0, 42u, 100u);
        EXPECT_NEAR(result, 105.12710963760242, 1e-12);
    }
    TEST(StudentTGbmTest, ProducesPositivePrice){
        const double result=student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 8.0, 42u, 100u);
        EXPECT_GT(result, 0.0);
    }
}