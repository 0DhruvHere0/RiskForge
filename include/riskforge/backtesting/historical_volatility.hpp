#pragma once
#include <span>
namespace riskforge::backtesting{
    [[nodiscard]]
    double annualized_historical_volatility(
        std::span<const double> log_returns,
        double periods_per_year
    );
}