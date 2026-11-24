#include "riskforge/backtesting/historical_returns.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    std::vector<double> historical_log_returns(std::span<const double> prices){
        if (prices.size()<2){
            throw std::invalid_argument("prices must contain at least two observations");
        }
        for (const double price: prices){
            if (!std::isfinite(price) || price<=0.0){
                throw std::invalid_argument("prices must be positive and finite");
            }
        }
        std::vector<double> returns;
        returns.reserve(prices.size()-1);
        for (std::size_t index=1; index<prices.size(); ++index){
            returns.push_back(std::log(prices[index]/prices[index-1]));
        }
        return returns;
    }
}