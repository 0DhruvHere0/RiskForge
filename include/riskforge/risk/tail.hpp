#pragma once
#include <cstddef>
#include <span>
namespace riskforge::risk{
    struct TailSummary{
        double threshold;
        double sum;
        std::size_t count;
    };
    [[nodiscard]]
    TailSummary aggregate_upper_tail(
        std::span<const double> losses,
        double tail_probability
    );
}