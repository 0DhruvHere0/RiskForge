#pragma once
#include <cstddef>
#include <span>
namespace riskforge::backtesting{
    struct UnconditionalCoverageResult{
        std::size_t observation_count;
        std::size_t exception_count;
        double observed_exception_rate;
        double expected_exception_rate;
        double likelihood_ratio;
        double p_value;
    };
    [[nodiscard]]
    UnconditionalCoverageResult evaluate_unconditional_coverage(
        std::span<const double> log_returns,
        double value_at_risk,
        double confidence_level
    );
}