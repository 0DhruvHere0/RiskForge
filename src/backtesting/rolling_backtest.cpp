#include "riskforge/backtesting/rolling_backtest.hpp"
#include <stdexcept>
namespace riskforge::backtesting{
    std::vector<BacktestReport> rolling_backtest_reports(
        std::span<const double> log_returns,
        std::size_t window_size,
        double value_at_risk,
        double periods_per_year
    ){
        if (window_size<2){
            throw std::invalid_argument("window_size must be at least two");
        }
        if (window_size>log_returns.size()){
            throw std::invalid_argument("window_size cannot exceed return count");
        }
        std::vector<BacktestReport> reports;
        reports.reserve(log_returns.size()-window_size+1);
        for (std::size_t start=0; start+window_size<=log_returns.size(); ++start){
            reports.push_back(
                create_backtest_report(
                    log_returns.subspan(start, window_size),
                    value_at_risk,
                    periods_per_year
                )
            );
        }
        return reports;
    }
}