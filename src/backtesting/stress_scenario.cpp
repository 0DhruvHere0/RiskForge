#include "riskforge/backtesting/stress_scenario.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    std::vector<double> apply_return_shock(
        std::span<const double> log_returns,
        double additive_shock
    ){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        if (!std::isfinite(additive_shock)){
            throw std::invalid_argument("additive_shock must be finite");
        }
        std::vector<double> stressed_returns;
        stressed_returns.reserve(log_returns.size());
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            stressed_returns.push_back(log_return+additive_shock);
        }
        return stressed_returns;
    }
}