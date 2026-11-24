#pragma once
#include <span>
namespace riskforge::backtesting{
    [[nodiscard]]
    double annualized_sharpe_ratio(
        std::span<const double> log_returns,
        double risk_free_rate_per_period,
        double periods_per_year
    );
}