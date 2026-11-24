#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace riskforge::simulation{
    [[nodiscard]]
    std::vector<double> parallel_stochastic_volatility_terminal_prices(
        double initial_price,
        double drift,
        double initial_variance,
        double long_term_variance,
        double mean_reversion,
        double volatility_of_variance,
        double time,
        std::size_t steps,
        std::size_t path_count,
        std::size_t worker_count,
        std::uint32_t seed
    );
}