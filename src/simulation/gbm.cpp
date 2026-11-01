#include "riskforge/simulation/gbm.hpp"
#include <cmath>
namespace riskforge::simulation{
    double gbm_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double standard_normal
    ){
        const double diffusion= volatility* std::sqrt(time)* standard_normal;
        const double deterministic_growth= (drift-0.5*volatility*volatility)*time;
        return initial_price* std::exp(deterministic_growth+ diffusion);
    }
}