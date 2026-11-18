#include "riskforge/risk/var.hpp"
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
                throw std::invalid_argument("initial_price must be positive");
            }
            if (!std::isfinite(drift)){
                throw std::invalid_argument("drift must be finite");
            }
            if (!std::isfinite(volatility)|| volatility<0.0){
                throw std::invalid_argument("volatility must be non-negative and finite");
            }
            if (!std::isfinite(time)|| time<0.0){
                throw std::invalid_argument("time must be non-negative and finite");
            }
            if (!std::isfinite(confidence_level)|| confidence_level<=0.0|| confidence_level>=1.0){
                throw std::invalid_argument("confidence must be between 0 and 1");
            }
        }
    }
    double lognormal_value_at_risk(
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
        const double z= random::normal_ppf(lower_tail_probability);
        const double log_return= (drift- 0.5*volatility*volatility)*time +volatility*std::sqrt(time)*z;
        const double lower_terminal_price= initial_price* std::exp(log_return);
        return initial_price-lower_terminal_price;
    }
}