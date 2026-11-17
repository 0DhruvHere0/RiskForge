#include "riskforge/risk/expected_shortfall.hpp"
#include "riskforge/random/normal.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::risk{
    namespace{
        void validate_inputs(
            double initial_price,
            double drift,
            double volatility,
            double time,
            double confidence_level
        ){
            if (!std::isfinite(initial_price)||initial_price<=0.0){
                throw std::invalid_argument("initial_price must be positive and finite");
            }
            if (!std::isfinite(drift)){
                throw std::invalid_argument("drift must be finite");
            }
            if (!std::isfinite(volatility)||volatility<0.0){
                throw std::invalid_argument("volatility must be non negative and finite");
            }
            if (!std::isfinite(time)||time<0.0){
                throw std::invalid_argument("time must be non-negative and finite");
            }
            if (!std::isfinite(confidence_level)||confidence_level<=0.0|| confidence_level>=1.0){
                throw std::invalid_argument("confidence_level must be between 0 and 1");
            }
        }
        double standard_normal_cdf(double value){
            constexpr double inverse_sqrt_two= 0.70710678118654752440;
            return 0.5* std::erfc(-value* inverse_sqrt_two);
        }
    }
    double lognormal_expected_shortfall(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double confidence_level
    ){
        validate_inputs(
            initial_price,
            drift,
            volatility,
            time,
            confidence_level
        );
        const double lower_tail_probability= 1.0- confidence_level;
        const double standard_normal_quantile= random::normal_ppf(lower_tail_probability);
        const double volatility_time= volatility* std::sqrt(time);
        const double conditional_price= initial_price* std::exp(drift*time)*standard_normal_cdf(standard_normal_quantile- volatility_time)/ lower_tail_probability;
        return initial_price- conditional_price;
    }
}