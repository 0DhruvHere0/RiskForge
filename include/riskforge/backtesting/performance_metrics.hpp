#pragma once
#include <span>
namespace riskforge::backtesting{
    struct PerformanceMetrics{
        double total_log_return;
        double total_compounded_return;
        double annualized_return;
    };
    [[nodiscard]]
    PerformanceMetrics calculate_performance_metrics(
        std::span<const double> log_returns,
        double periods_per_year
    );
}