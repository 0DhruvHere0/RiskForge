#include "riskforge/risk/tail_accumulator.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <vector>
namespace riskforge::risk{
    AdaptiveTailAccumulator::AdaptiveTailAccumulator(
        std::size_t observation_count,
        double tail_probability
    )
        : observation_count_(observation_count),
          tail_count_(0),
          values_seen_(0),
          largest_losses_(){
        if (observation_count== 0){
            throw std::invalid_argument("observation_count must be greater than zero");
        }
        if (!std::isfinite(tail_probability)|| tail_probability <= 0.0 || tail_probability > 1.0){
            throw std::invalid_argument("tail_probability must be in (0, 1]");
        }
        tail_count_= std::max<std::size_t>(
            1,
            static_cast<std::size_t>(
                std::ceil(tail_probability *static_cast<double>(observation_count)
                )
            )
        );
        largest_losses_.reserve(tail_count_);
    }
    void AdaptiveTailAccumulator::add(double loss){
        if (!std::isfinite(loss)){
            throw std::invalid_argument("loss must be finite");
        }
        if (values_seen_ >= observation_count_){
            throw std::logic_error("all expected observations have been added");
        }
        ++values_seen_;
        largest_losses_.push_back(loss);
        std::sort(
            largest_losses_.begin(),
            largest_losses_.end(),
            std::greater<double>()
        );
        if (largest_losses_.size()> tail_count_){
            largest_losses_.pop_back();
        }
    }
    TailSummary AdaptiveTailAccumulator::finalize() const{
        if (values_seen_ != observation_count_){
            throw std::logic_error("not all expected observations have been added");
        }
        const double tail_sum= std::accumulate(
            largest_losses_.begin(),
            largest_losses_.end(),
            0.0
        );
        return TailSummary{
            largest_losses_.back(),
            tail_sum,
            tail_count_
        };
    }
}