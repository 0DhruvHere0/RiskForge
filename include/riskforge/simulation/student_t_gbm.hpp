#pragma once
#include <cstdint>
namespace riskforge::simulation{
    [[nodiscard]]
    double student_t_gbm_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double degrees_of_freedom,
        std::uint32_t seed,
        std::uint64_t sample
    );
}