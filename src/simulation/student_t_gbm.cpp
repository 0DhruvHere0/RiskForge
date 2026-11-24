#include "riskforge/simulation/student_t_gbm.hpp"
#include "riskforge/random/student_t.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::simulation{
    double student_t_gbm_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double degrees_of_freedom,
        std::uint32_t seed,
        std::uint64_t sample
    ){
        if (!std::isfinite(initial_price) || initial_price<=0.0){
            throw std::invalid_argument("initial_price must be positive and finite");
        }
        if (!std::isfinite(drift)){
            throw std::invalid_argument("drift must be finite");
        }
        if (!std::isfinite(volatility) || volatility<0.0){
            throw std::invalid_argument("volatility must be non-negative and finite");
        }
        if (!std::isfinite(time) || time<0.0){
            throw std::invalid_argument("time must be non-negative and finite");
        }
        if (!std::isfinite(degrees_of_freedom) || degrees_of_freedom<=2.0){
            throw std::invalid_argument("degrees_of_freedom must be greater than 2");
        }
        const double student_t=riskforge::random::student_t_sample(degrees_of_freedom, seed, sample);
        const double standardized_student_t=student_t*std::sqrt((degrees_of_freedom-2.0)/degrees_of_freedom);
        const double log_return=(drift-0.5*volatility*volatility)*time+volatility*std::sqrt(time)*standardized_student_t;
        return initial_price*std::exp(log_return);
    }
}