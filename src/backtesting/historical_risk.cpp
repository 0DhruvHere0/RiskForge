#include "riskforge/backtesting/historical_risk.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>
namespace riskforge::backtesting{
    HistoricalRiskResult estimate_historical_risk(
        std::span<const double> log_returns,
        double confidence_level
    ){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        if (!std::isfinite(confidence_level) || confidence_level<=0.0 || confidence_level>=1.0){
            throw std::invalid_argument("confidence_level must be between zero and one");
        }
        std::vector<double> losses;
        losses.reserve(log_returns.size());
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            losses.push_back(-log_return);
        }
        std::sort(losses.begin(), losses.end());
        const auto raw_index=static_cast<std::size_t>(
            std::ceil(confidence_level*static_cast<double>(losses.size()))
        );
        const std::size_t var_index=std::min(raw_index, losses.size())-1;
        const double value_at_risk=losses[var_index];
        double tail_sum=0.0;
        std::size_t tail_count=0;
        for (const double loss: losses){
            if (loss>=value_at_risk){
                tail_sum+=loss;
                ++tail_count;
            }
        }
        return HistoricalRiskResult{
            value_at_risk,
            tail_sum/static_cast<double>(tail_count)
        };
    }
}