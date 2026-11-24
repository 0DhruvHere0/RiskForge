#include "riskforge/options/monte_carlo_options.hpp"
#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
namespace riskforge::options{
    namespace{
        void validate_option_input(double strike, double risk_free_rate, std::size_t worker_count){
            if (!std::isfinite(strike) || strike<=0.0){
                throw std::invalid_argument("strike must be positive and finite");
            }
            if (!std::isfinite(risk_free_rate)){
                throw std::invalid_argument("risk free rate must be finite");
            }
            if (worker_count==0){
                throw std::invalid_argument("worker_count must be greater than zero");
            }
        }
    }
    double monte_carlo_european_call_price(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count){
        validate_option_input(strike, risk_free_rate, worker_count);
        const auto terminal_prices=simulation::simulate_gbm_terminal_prices_parallel(config, worker_count);
        double payoff_sum=0.0;
        for (const double terminal_price : terminal_prices){
            payoff_sum+=std::max(terminal_price-strike, 0.0);
        }
        return std::exp(-risk_free_rate*config.time)*payoff_sum/static_cast<double>(terminal_prices.size());
    }
    double monte_carlo_european_put_price(const simulation::GbmSimulationConfig& config, double strike, double risk_free_rate, std::size_t worker_count){
        validate_option_input(strike, risk_free_rate, worker_count);
        const auto terminal_prices=simulation::simulate_gbm_terminal_prices_parallel(config, worker_count);
        double payoff_sum=0.0;
        for (const double terminal_price : terminal_prices){
            payoff_sum+=std::max(strike-terminal_price, 0.0);
        }
        return std::exp(-risk_free_rate*config.time)*payoff_sum/static_cast<double>(terminal_prices.size());
    }
}