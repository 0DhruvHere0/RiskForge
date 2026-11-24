#include "riskforge/simulation/jump_diffusion.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::jump_diffusion_terminal_price;
    TEST(JumpDiffusionValidationTest, RejectsNegativeJumpIntensity){
        EXPECT_THROW(static_cast<void>(jump_diffusion_terminal_price(100.0, 0.05, 0.20, -0.4, -0.10, 0.20, 1.0, 42u, 100u)), std::invalid_argument);
    }
    TEST(JumpDiffusionValidationTest, RejectsNegativeJumpVolatility){
        EXPECT_THROW(static_cast<void>(jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, -0.20, 1.0, 42u, 100u)), std::invalid_argument);
    }
    TEST(JumpDiffusionValidationTest, RejectsNonPositiveInitialPrice){
        EXPECT_THROW(static_cast<void>(jump_diffusion_terminal_price(0.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, 100u)), std::invalid_argument);
    }
}