#pragma once
#include <cstddef>
#include <span>
namespace riskforge::risk{
    struct QuantileConfidenceInterval{
        double lower_value;
        double upper_value;
        std::size_t lower_index;
        std::size_t upper_index;
    };
    [[nodiscard]]
    QuantileConfidenceInterval order_statistic_quantile_ci(
        std::span<const double> samples,
        double quantile,
        double confidence_level
    );
}