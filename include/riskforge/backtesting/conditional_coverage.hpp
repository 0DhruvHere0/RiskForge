#pragma once
#include <cstddef>
#include <span>
namespace riskforge::backtesting{
    struct ConditionalCoverageResult{
        std::size_t observation_count;
        std::size_t exception_count;
        double independence_likelihood_ratio;
        double independence_p_value;
        double conditional_likelihood_ratio;
        double conditional_p_value;
    };
    [[nodiscard]]
    ConditionalCoverageResult evaluate_conditional_coverage(
        std::span<const double> log_returns,
        double value_at_risk,
        double confidence_level
    );
}