#pragma once
#include <cstddef>
#include <span>
namespace riskforge::backtesting{
    struct VarBacktestResult{
        std::size_t observation_count;
        std::size_t exception_count;
        double exception_rate;
    };
    [[nodiscard]]
    VarBacktestResult backtest_value_at_risk(
        std::span<const double> log_returns,
        double value_at_risk
    );
}