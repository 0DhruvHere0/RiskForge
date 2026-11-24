#pragma once
#include <cstddef>
#include <cstdint>
namespace riskforge::simulation{
    [[nodiscard]]
    double stochastic_volatility_terminal_price(
        double initial_price,
        double drift,
        double initial_variance,
        double long_term_variance,
        double mean_reversion,
        double volatility_of_variance,
        double time,
        std::size_t steps,
        std::uint32_t seed,
        std::uint64_t sample
    );
}