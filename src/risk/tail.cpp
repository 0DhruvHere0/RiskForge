#include "riskforge/risk/tail.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <vector>
namespace riskforge::risk{
    TailSummary aggregate_upper_tail(
        std::span<const double> losses,
        double tail_probability
    ){
        if (losses.empty()){
            throw std::invalid_argument(
                "losses must not be empty"
            );
        }
        if (!std::isfinite(tail_probability)||
        tail_probability<= 0.0 ||
        tail_probability> 1.0){
            throw std::invalid_argument(
                "tail_probability must be in (0,1)"
            );
        }
        std::vector<double> sorted_losses(
            losses.begin(),
            losses.end()
        );
        std::sort(
            sorted_losses.begin(),
            sorted_losses.end(),
            std::greater<double>());
        const std::size_t tail_count= std::max<std::size_t>(
            1,
            static_cast<std::size_t>(
                std::ceil(
                    tail_probability* static_cast<double>(sorted_losses.size())
                )
            )
        );
        const double tail_sum= std::accumulate(
            sorted_losses.begin(),
            sorted_losses.begin()+ tail_count,
            0.0
        );
        return TailSummary{
            sorted_losses[tail_count-1],
            tail_sum,
            tail_count   
        };
    }
}