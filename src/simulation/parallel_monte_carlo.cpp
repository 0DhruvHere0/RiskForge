#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include "riskforge/simulation/gbm.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <thread>
#include <vector>
namespace riskforge::simulation{
    namespace{
        void validate_config(
            const GbmSimulationConfig& config,
            std::size_t worker_count
        ){
            if (!std::isfinite(config.initial_price) ||
                config.initial_price <= 0.0){
                throw std::invalid_argument(
                    "initial_price must be positive and finite"
                );
            }
            if (!std::isfinite(config.drift)){
                throw std::invalid_argument(
                    "drift must be finite"
                );
            }
            if (!std::isfinite(config.volatility) ||
                config.volatility < 0.0){
                throw std::invalid_argument(
                    "volatility must be non-negative and finite"
                );
            }
            if (!std::isfinite(config.time) ||
                config.time < 0.0){
                throw std::invalid_argument(
                    "time must be non-negative and finite"
                );
            }
            if (config.path_count == 0){
                throw std::invalid_argument(
                    "path_count must be greater than zero"
                );
            }
            if (worker_count == 0){
                throw std::invalid_argument(
                    "worker_count must be greater than zero"
                );
            }
        }
        double generate_price(
            const GbmSimulationConfig& config,
            std::size_t path
        ){
            const std::uint64_t path_index=
                static_cast<std::uint64_t>(path);
            const riskforge::random::Philox4x32_10::Key key{
                config.seed,
                config.seed^0x9E3779B9u
            };
            const riskforge::random::Philox4x32_10::Counter counter{
                static_cast<std::uint32_t>(path_index),
                static_cast<std::uint32_t>(path_index>>32u),
                0u,
                0u
            };
            const auto block=
                riskforge::random::Philox4x32_10::generate(
                    counter,
                    key
                );
            const double uniform=
                riskforge::random::uniform_open01(
                    block[0],
                    block[1]
                );
            const double standard_normal=
                riskforge::random::normal_ppf(uniform);
            return riskforge::simulation::gbm_terminal_price(
                config.initial_price,
                config.drift,
                config.volatility,
                config.time,
                standard_normal
            );
        }
    }
    std::vector<double> simulate_gbm_terminal_prices_parallel(
        const GbmSimulationConfig& config,
        std::size_t worker_count
    ){
        validate_config(config, worker_count);
        std::vector<double> terminal_prices(config.path_count);
        const std::size_t thread_count=
            std::min(worker_count, config.path_count);
        std::vector<std::thread> workers;
        workers.reserve(thread_count);
        const std::size_t base_size=
            config.path_count/thread_count;
        const std::size_t remainder=
            config.path_count%thread_count;
        std::size_t begin=0;
        for (std::size_t worker=0;
             worker<thread_count;
             ++worker){
            const std::size_t block_size=
                base_size+(worker<remainder ? 1u:0u);
            const std::size_t end=begin+block_size;
            workers.emplace_back(
                [&config,&terminal_prices,begin,end](){
                    for (std::size_t path=begin;
                         path<end;
                         ++path){
                        terminal_prices[path]=
                            generate_price(config,path);
                    }
                }
            );
            begin=end;
        }
        for (auto& worker : workers){
            worker.join();
        }
        return terminal_prices;
    }
}