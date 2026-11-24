#include "riskforge/backtesting/var_backtest.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    VarBacktestResult backtest_value_at_risk(
        std::span<const double> log_returns,
        double value_at_risk
    ){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        if (!std::isfinite(value_at_risk)){
            throw std::invalid_argument("value_at_risk must be finite");
        }
        std::size_t exception_count=0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            if (-log_return>value_at_risk){
                ++exception_count;
            }
        }
        return VarBacktestResult{
            log_returns.size(),
            exception_count,
            static_cast<double>(exception_count)/static_cast<double>(log_returns.size())
        };
    }
}