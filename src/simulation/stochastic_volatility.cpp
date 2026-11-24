#include "riskforge/simulation/stochastic_volatility.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>
namespace riskforge::simulation{
    double stochastic_volatility_terminal_price(
        double initial_price,
        double drift,
        double initial_variance,
        double long_term_variance,
        double mean_reversion,
        double volatility_of_variance,
        double time,
        std::size_t steps,
        std::uint32_t seed,
        std::uint64_t sample
    ){
        if (!std::isfinite(initial_price) || initial_price<=0.0){
            throw std::invalid_argument("initial_price must be positive and finite");
        }
        if (!std::isfinite(drift)){
            throw std::invalid_argument("drift must be finite");
        }
        if (!std::isfinite(initial_variance) || initial_variance<0.0){
            throw std::invalid_argument("initial_variance must be non-negative and finite");
        }
        if (!std::isfinite(long_term_variance) || long_term_variance<0.0){
            throw std::invalid_argument("long_term_variance must be non-negative and finite");
        }
        if (!std::isfinite(mean_reversion) || mean_reversion<=0.0){
            throw std::invalid_argument("mean_reversion must be positive and finite");
        }
        if (!std::isfinite(volatility_of_variance) || volatility_of_variance<0.0){
            throw std::invalid_argument("volatility_of_variance must be non-negative and finite");
        }
        if (!std::isfinite(time) || time<0.0){
            throw std::invalid_argument("time must be non-negative and finite");
        }
        if (steps==0){
            throw std::invalid_argument("steps must be greater than zero");
        }
        const double dt=time/static_cast<double>(steps);
        const double square_root_dt=std::sqrt(dt);
        double price=initial_price;
        double variance=initial_variance;
        const riskforge::random::Philox4x32_10::Key key{
            seed,
            seed^0x9E3779B9u
        };
        for (std::size_t step=0; step<steps; ++step){
            const std::uint64_t step_index=static_cast<std::uint64_t>(step);
            const riskforge::random::Philox4x32_10::Counter counter{
                static_cast<std::uint32_t>(sample),
                static_cast<std::uint32_t>(sample>>32u),
                static_cast<std::uint32_t>(step_index),
                static_cast<std::uint32_t>(step_index>>32u)
            };
            const auto block=riskforge::random::Philox4x32_10::generate(counter, key);
            const double price_normal=riskforge::random::normal_ppf(riskforge::random::uniform_open01(block[0], block[1]));
            const double variance_normal=riskforge::random::normal_ppf(riskforge::random::uniform_open01(block[2], block[3]));
            const double current_variance=std::max(variance, 0.0);
            const double variance_diffusion=volatility_of_variance*std::sqrt(current_variance)*square_root_dt*variance_normal;
            variance=std::max(0.0, variance+mean_reversion*(long_term_variance-current_variance)*dt+variance_diffusion);
            price*=std::exp((drift-0.5*current_variance)*dt+std::sqrt(current_variance)*square_root_dt*price_normal);
        }
        return price;
    }
}