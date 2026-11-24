#include "riskforge/backtesting/historical_volatility.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    double annualized_historical_volatility(
        std::span<const double> log_returns,
        double periods_per_year
    ){
        if (log_returns.size()<2){
            throw std::invalid_argument("at least two returns are required");
        }
        if (!std::isfinite(periods_per_year) || periods_per_year<=0.0){
            throw std::invalid_argument("periods_per_year must be positive and finite");
        }
        double sum=0.0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            sum+=log_return;
        }
        const double mean=sum/static_cast<double>(log_returns.size());
        double squared_deviation_sum=0.0;
        for (const double log_return: log_returns){
            const double deviation=log_return-mean;
            squared_deviation_sum+=deviation*deviation;
        }
        const double variance=squared_deviation_sum/
            static_cast<double>(log_returns.size()-1);
        return std::sqrt(variance*periods_per_year);
    }
}