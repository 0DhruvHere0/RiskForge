#include "riskforge/risk/order_statistic_ci.hpp"
#include "riskforge/random/normal.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>
namespace riskforge::risk{
    QuantileConfidenceInterval order_statistic_quantile_ci(
        std::span<const double> samples,
        double quantile,
        double confidence_level
    ){
        if (samples.empty()){
            throw std::invalid_argument(
                "samples must not be empty"
            );
        }
        if (!std::isfinite(quantile) ||
            quantile <= 0.0 ||
            quantile >= 1.0){
            throw std::invalid_argument(
                "quantile must be between 0 and 1"
            );
        }
        if (!std::isfinite(confidence_level) ||
            confidence_level <= 0.0 ||
            confidence_level >= 1.0){
            throw std::invalid_argument(
                "confidence_level must be between 0 and 1"
            );
        }
        std::vector<double> sorted_samples(
            samples.begin(),
            samples.end()
        );
        if (!std::all_of(
                sorted_samples.begin(),
                sorted_samples.end(),
                [](double value){
                    return std::isfinite(value);
                }
            )){
            throw std::invalid_argument(
                "samples must contain only finite values"
            );
        }
        std::sort(
            sorted_samples.begin(),
            sorted_samples.end()
        );
        const double sample_count=
            static_cast<double>(sorted_samples.size());
        const double z=
            riskforge::random::normal_ppf(
                0.5+0.5*confidence_level
            );
        const double mean=
            sample_count*quantile;
        const double standard_deviation=
            std::sqrt(
                sample_count*
                quantile*
                (1.0-quantile)
            );
        const double lower_rank=
            std::ceil(mean-z*standard_deviation);
        const double upper_rank=
            std::floor(mean+z*standard_deviation);
        const std::size_t lower_index=
            std::min<std::size_t>(
                sorted_samples.size()-1,
                std::max<std::size_t>(
                    0,
                    lower_rank <= 1.0
                        ? 0
                        : static_cast<std::size_t>(
                            lower_rank-1.0
                        )
                )
            );
        const std::size_t upper_index=
            std::min<std::size_t>(
                sorted_samples.size()-1,
                std::max<std::size_t>(
                    0,
                    upper_rank <= 1.0
                        ? 0
                        : static_cast<std::size_t>(
                            upper_rank-1.0
                        )
                )
            );
        return QuantileConfidenceInterval{
            sorted_samples[lower_index],
            sorted_samples[upper_index],
            lower_index,
            upper_index
        };
    }
}