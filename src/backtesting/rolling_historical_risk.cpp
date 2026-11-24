#include "riskforge/backtesting/rolling_historical_risk.hpp"
#include <stdexcept>
namespace riskforge::backtesting{
    std::vector<HistoricalRiskResult> rolling_historical_risk(
        std::span<const double> log_returns,
        std::size_t window_size,
        double confidence_level
    ){
        if (window_size<2){
            throw std::invalid_argument("window_size must be at least two");
        }
        if (window_size>log_returns.size()){
            throw std::invalid_argument("window_size cannot exceed return count");
        }
        std::vector<HistoricalRiskResult> results;
        results.reserve(log_returns.size()-window_size+1);
        for (std::size_t start=0; start+window_size<=log_returns.size(); ++start){
            results.push_back(
                estimate_historical_risk(
                    log_returns.subspan(start, window_size),
                    confidence_level
                )
            );
        }
        return results;
    }
}