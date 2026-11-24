#pragma once
#include <cstdint>
namespace riskforge::simulation{
    [[nodiscard]]
    double jump_diffusion_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double jump_intensity,
        double jump_mean,
        double jump_volatility,
        double time,
        std::uint32_t seed,
        std::uint64_t sample
    );
}