#include "riskforge/backtesting/conditional_coverage.hpp"
#include "riskforge/backtesting/unconditional_coverage.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>
namespace riskforge::backtesting{
    namespace{
        double bernoulli_log_likelihood(
            std::size_t failures,
            std::size_t successes,
            double probability
        ){
            double result=0.0;
            if (successes>0){
                result+=static_cast<double>(successes)*std::log(probability);
            }
            if (failures>0){
                result+=static_cast<double>(failures)*
                    std::log1p(-probability);
            }
            return result;
        }
    }
    ConditionalCoverageResult evaluate_conditional_coverage(
        std::span<const double> log_returns,
        double value_at_risk,
        double confidence_level
    ){
        if (log_returns.size()<2){
            throw std::invalid_argument("at least two returns are required");
        }
        if (!std::isfinite(value_at_risk)){
            throw std::invalid_argument("value_at_risk must be finite");
        }
        if (!std::isfinite(confidence_level) || confidence_level<=0.0 || confidence_level>=1.0){
            throw std::invalid_argument("confidence_level must be between zero and one");
        }
        std::vector<bool> exceptions;
        exceptions.reserve(log_returns.size());
        for (const double log_return: log_returns){
            if (!std::isfinite(log_return)){
                throw std::invalid_argument("log_returns must be finite");
            }
            exceptions.push_back(-log_return>value_at_risk);
        }
        std::size_t n00=0;
        std::size_t n01=0;
        std::size_t n10=0;
        std::size_t n11=0;
        for (std::size_t index=1; index<exceptions.size(); ++index){
            if (!exceptions[index-1] && !exceptions[index]){
                ++n00;
            }
            else if (!exceptions[index-1] && exceptions[index]){
                ++n01;
            }
            else if (exceptions[index-1] && !exceptions[index]){
                ++n10;
            }
            else{
                ++n11;
            }
        }
        const std::size_t transition_count=log_returns.size()-1;
        const std::size_t total_exceptions=n01+n11;
        const double common_probability=
            static_cast<double>(total_exceptions)/
            static_cast<double>(transition_count);
        const double probability_after_no_exception=
            n00+n01==0
                ? 0.0
                : static_cast<double>(n01)/
                    static_cast<double>(n00+n01);
        const double probability_after_exception=
            n10+n11==0
                ? 0.0
                : static_cast<double>(n11)/
                    static_cast<double>(n10+n11);
        const double restricted_log_likelihood=
            bernoulli_log_likelihood(
                n00+n10,
                n01+n11,
                common_probability
            );
        const double unrestricted_log_likelihood=
            bernoulli_log_likelihood(
                n00,
                n01,
                probability_after_no_exception
            )+
            bernoulli_log_likelihood(
                n10,
                n11,
                probability_after_exception
            );
        const double independence_likelihood_ratio=std::max(
            0.0,
            2.0*(
                unrestricted_log_likelihood-
                restricted_log_likelihood
            )
        );
        const auto unconditional=evaluate_unconditional_coverage(
            log_returns,
            value_at_risk,
            confidence_level
        );
        const double conditional_likelihood_ratio=
            unconditional.likelihood_ratio+
            independence_likelihood_ratio;
        return ConditionalCoverageResult{
            log_returns.size(),
            exceptions.empty()
                ? 0u
                : static_cast<std::size_t>(
                    std::count(exceptions.begin(), exceptions.end(), true)
                ),
            independence_likelihood_ratio,
            std::erfc(
                std::sqrt(independence_likelihood_ratio/2.0)
            ),
            conditional_likelihood_ratio,
            std::exp(-conditional_likelihood_ratio/2.0)
        };
    }
}