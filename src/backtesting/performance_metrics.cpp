#include "riskforge/backtesting/performance_metrics.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    PerformanceMetrics calculate_performance_metrics(
        std::span<const double> log_returns,
        double periods_per_year
    ){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        if (!std::isfinite(periods_per_year) || periods_per_year<=0.0){
            throw std::invalid_argument("periods_per_year must be positive and finite");
        }
        double total_log_return=0.0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            total_log_return+=log_return;
        }
        const double annualized_log_return=
            total_log_return*periods_per_year/
            static_cast<double>(log_returns.size());
        return PerformanceMetrics{
            total_log_return,
            std::expm1(total_log_return),
            std::expm1(annualized_log_return)
        };
    }
}