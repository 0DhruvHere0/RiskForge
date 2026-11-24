#include "riskforge/backtesting/unconditional_coverage.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace riskforge::backtesting{
    namespace{
        double log_likelihood(
            std::size_t observations,
            std::size_t exceptions,
            double exception_rate
        ){
            double result=0.0;
            if (exceptions>0){
                result+=static_cast<double>(exceptions)*std::log(exception_rate);
            }
            if (exceptions<observations){
                result+=static_cast<double>(observations-exceptions)*
                    std::log1p(-exception_rate);
            }
            return result;
        }
    }
    UnconditionalCoverageResult evaluate_unconditional_coverage(
        std::span<const double> log_returns,
        double value_at_risk,
        double confidence_level
    ){
        if (log_returns.empty()){
            throw std::invalid_argument("log_returns must not be empty");
        }
        if (!std::isfinite(value_at_risk)){
            throw std::invalid_argument("value_at_risk must be finite");
        }
        if (!std::isfinite(confidence_level) || confidence_level<=0.0 || confidence_level>=1.0){
            throw std::invalid_argument("confidence_level must be between zero and one");
        }
        std::size_t exception_count=0;
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            if (-log_return>value_at_risk){
                ++exception_count;
            }
        }
        const double expected_rate=1.0-confidence_level;
        const double observed_rate=
            static_cast<double>(exception_count)/
            static_cast<double>(log_returns.size());
        const double null_log_likelihood=log_likelihood(
            log_returns.size(),
            exception_count,
            expected_rate
        );
        const double alternative_log_likelihood=log_likelihood(
            log_returns.size(),
            exception_count,
            observed_rate
        );
        const double likelihood_ratio=std::max(
            0.0,
            2.0*(alternative_log_likelihood-null_log_likelihood)
        );
        const double p_value=std::erfc(
            std::sqrt(likelihood_ratio/2.0)
        );
        return UnconditionalCoverageResult{
            log_returns.size(),
            exception_count,
            observed_rate,
            expected_rate,
            likelihood_ratio,
            p_value
        };
    }
}