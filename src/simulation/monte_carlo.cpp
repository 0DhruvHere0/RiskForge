#include "riskforge/simulation/monte_carlo.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include "riskforge/simulation/gbm.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>
namespace riskforge::simulation{
    std::vector<double> simulate_gbm_terminal_prices(
        const GbmSimulationConfig& config
    ){
        if (!std::isfinite(config.initial_price)||config.initial_price<=0.0){
            throw std::invalid_argument("initial price must be positive and finite");
        }
        if (!std::isfinite(config.drift)){
            throw std::invalid_argument("drift must be finite");
        }
        if (!std::isfinite(config.volatility)||config.volatility<0.0){
            throw std::invalid_argument("volatility must be non-negative and finite");
        }
        if (!std::isfinite(config.time)||config.time<0.0){
            throw std::invalid_argument("time must be non-negative and finite");
        }
        if (config.path_count==0){
            throw std::invalid_argument("path_count must be greater than 0");
        }
        std::vector<double> terminal_price;
        terminal_price.reserve(config.path_count);
        const riskforge::random::Philox4x32_10::Key key{
            config.seed,
            config.seed^ 0x9E3779B9u
        };
        for (std::size_t path= 0; path<config.path_count; ++path){
            const std::uint64_t path_index= static_cast<std::uint64_t>(path);
            const riskforge::random::Philox4x32_10::Counter counter{
                static_cast<std::uint32_t>(path_index),
                static_cast<std::uint32_t>(path_index >>32),
                0u,
                0u
            };
            const auto block= riskforge::random::Philox4x32_10::generate(
                counter,
                key
            );
            const double uniform= riskforge::random::uniform_open01(
                block[0],
                block[1]
            );
            const double standard_normal= riskforge::random::normal_ppf(uniform);
            terminal_price.push_back(
                gbm_terminal_price(
                    config.initial_price,
                    config.drift,
                    config.volatility,
                    config.time,
                    standard_normal
                )
            );
        }
        return terminal_price;
    }
}