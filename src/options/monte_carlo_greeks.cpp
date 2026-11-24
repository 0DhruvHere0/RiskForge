#include "riskforge/options/monte_carlo_greeks.hpp"
#include "riskforge/options/monte_carlo_options.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
namespace riskforge::options{
    namespace{
        void validate_bump(double bump){
            if (!std::isfinite(bump) || bump<=0.0){
                throw std::invalid_argument("bump must be positive and finite");
            }
        }
    }
    double monte_carlo_call_delta(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double spot_bump){
        validate_bump(spot_bump);
        simulation::GbmSimulationConfig up=config;
        simulation::GbmSimulationConfig down=config;
        up.initial_price+=spot_bump;
        down.initial_price-=spot_bump;
        if (down.initial_price<=0.0){
            throw std::invalid_argument("spot bump produces non-positive price");
        }
        const double up_price=monte_carlo_european_call_price(up, strike, risk_free_rate, worker_count);
        const double down_price=monte_carlo_european_call_price(down, strike, risk_free_rate, worker_count);
        return (up_price-down_price)/(2.0*spot_bump);
    }
    double monte_carlo_call_gamma(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double spot_bump){
        validate_bump(spot_bump);
        simulation::GbmSimulationConfig up=config;
        simulation::GbmSimulationConfig down=config;
        up.initial_price+=spot_bump;
        down.initial_price-=spot_bump;
        if (down.initial_price<=0.0){
            throw std::invalid_argument("spot bump produces non-positive price");
        }
        const double base_price=monte_carlo_european_call_price(config, strike, risk_free_rate, worker_count);
        const double up_price=monte_carlo_european_call_price(up, strike, risk_free_rate, worker_count);
        const double down_price=monte_carlo_european_call_price(down, strike, risk_free_rate, worker_count);
        return (up_price-2.0*base_price+down_price)/(spot_bump*spot_bump);
    }
    double monte_carlo_call_vega(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count, double volatility_bump){
        validate_bump(volatility_bump);
        simulation::GbmSimulationConfig up=config;
        simulation::GbmSimulationConfig down=config;
        up.volatility+=volatility_bump;
        down.volatility=std::max(0.0, down.volatility-volatility_bump);
        const double up_price=monte_carlo_european_call_price(up, strike, risk_free_rate, worker_count);
        const double down_price=monte_carlo_european_call_price(down, strike, risk_free_rate, worker_count);
        return (up_price-down_price)/(up.volatility-down.volatility);
    }
}