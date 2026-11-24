#include "riskforge/simulation/jump_diffusion.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::jump_diffusion_terminal_price;
    TEST(JumpDiffusionTest, SameSeedAndSampleAreDeterministic){
        const double first=jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, 100u);
        const double second=jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, 100u);
        EXPECT_DOUBLE_EQ(first, second);
    }
    TEST(JumpDiffusionTest, ZeroVolatilityAndZeroJumpsProduceDeterministicGrowth){
        const double result=jump_diffusion_terminal_price(100.0, 0.05, 0.0, 0.0, 0.0, 0.0, 1.0, 42u, 100u);
        EXPECT_NEAR(result, 105.12710963760242, 1e-12);
    }
    TEST(JumpDiffusionTest, ProducesPositivePrice){
        const double result=jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, 100u);
        EXPECT_GT(result, 0.0);
    }
}