#include "riskforge/backtesting/sharpe_ratio.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    double annualized_sharpe_ratio(
        std::span<const double> log_returns,
        double risk_free_rate_per_period,
        double periods_per_year
    ){
        if (log_returns.size()<2){
            throw std::invalid_argument("at least two returns are required");
        }
        if (!std::isfinite(risk_free_rate_per_period)){
            throw std::invalid_argument("risk_free_rate_per_period must be finite");
        }
        if (!std::isfinite(periods_per_year) || periods_per_year<=0.0){
            throw std::invalid_argument("periods_per_year must be positive and finite");
        }
        double excess_sum=0.0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            excess_sum+=log_return-risk_free_rate_per_period;
        }
        const double mean_excess=excess_sum/
            static_cast<double>(log_returns.size());
        double squared_deviation_sum=0.0;
        for (const double log_return: log_returns){
            const double deviation=
                log_return-risk_free_rate_per_period-mean_excess;
            squared_deviation_sum+=deviation*deviation;
        }
        const double standard_deviation=std::sqrt(
            squared_deviation_sum/
            static_cast<double>(log_returns.size()-1)
        );
        if (standard_deviation==0.0){
            throw std::domain_error(
                "Sharpe ratio is undefined for zero volatility"
            );
        }
        return mean_excess/standard_deviation*std::sqrt(periods_per_year);
    }
}