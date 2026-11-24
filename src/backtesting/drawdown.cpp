#include "riskforge/backtesting/drawdown.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
namespace riskforge::backtesting{
    double maximum_drawdown(std::span<const double> log_returns){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        double portfolio_value=1.0;
        double peak_value=1.0;
        double maximum_drawdown_value=0.0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            portfolio_value*=std::exp(log_return);
            peak_value=std::max(peak_value, portfolio_value);
            const double drawdown=(peak_value-portfolio_value)/peak_value;
            maximum_drawdown_value=std::max(
                maximum_drawdown_value,
                drawdown
            );
        }
        return maximum_drawdown_value;
    }
}