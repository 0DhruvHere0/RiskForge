#include "riskforge/options/greeks.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::options{
    namespace{
        double normal_pdf(double value){
            return std::exp(-0.5*value*value)/std::sqrt(2.0*std::acos(-1.0));
        }
        double normal_cdf(double value){
            return 0.5*std::erfc(-value/std::sqrt(2.0));
        }
        double d1(const BlackScholesInput& input){
            static_cast<void>(black_scholes_call_price(input));
            if (input.volatility==0.0 || input.time==0.0){
                throw std::domain_error("volatility and time must be positive");
            }
            return (std::log(input.spot/input.strike)+(input.risk_free_rate+0.5*input.volatility*input.volatility)*input.time)/(input.volatility*std::sqrt(input.time));
        }
    }
    double black_scholes_call_gamma(const BlackScholesInput& input){
        const double value=d1(input);
        return normal_pdf(value)/(input.spot*input.volatility*std::sqrt(input.time));
    }
    double black_scholes_call_vega(const BlackScholesInput& input){
        const double value=d1(input);
        return input.spot*normal_pdf(value)*std::sqrt(input.time);
    }
    double black_scholes_call_theta(const BlackScholesInput& input){
        const double first_term=-input.spot*normal_pdf(d1(input))*input.volatility/(2.0*std::sqrt(input.time));
        const double d2_value=d1(input)-input.volatility*std::sqrt(input.time);
        const double second_term=input.risk_free_rate*input.strike*std::exp(-input.risk_free_rate*input.time)*normal_cdf(d2_value);
        return first_term-second_term;
    }
    double black_scholes_call_rho(const BlackScholesInput& input){
        const double d2_value=d1(input)-input.volatility*std::sqrt(input.time);
        return input.strike*input.time*std::exp(-input.risk_free_rate*input.time)*normal_cdf(d2_value);
    }
}