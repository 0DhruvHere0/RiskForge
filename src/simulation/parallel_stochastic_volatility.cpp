#include "riskforge/simulation/parallel_stochastic_volatility.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include <stdexcept>
#include <thread>
#include <vector>
#include <algorithm>
namespace riskforge::simulation{
    std::vector<double> parallel_stochastic_volatility_terminal_prices(
        double initial_price,
        double drift,
        double initial_variance,
        double long_term_variance,
        double mean_reversion,
        double volatility_of_variance,
        double time,
        std::size_t steps,
        std::size_t path_count,
        std::size_t worker_count,
        std::uint32_t seed
    ){
        if (path_count==0){
            throw std::invalid_argument("path_count must be greater than zero");
        }
        if (worker_count==0){
            throw std::invalid_argument("worker_count must be greater than zero");
        }
        const std::size_t thread_count=std::min(worker_count, path_count);
        std::vector<double> terminal_prices(path_count);
        std::vector<std::thread> workers;
        workers.reserve(thread_count);
        const std::size_t block_size=path_count/thread_count;
        const std::size_t remainder=path_count%thread_count;
        std::size_t begin=0;
        for (std::size_t worker=0; worker<thread_count; ++worker){
            const std::size_t count=block_size+(worker<remainder ? 1u : 0u);
            const std::size_t end=begin+count;
            workers.emplace_back([&, begin, end](){
                for (std::size_t path=begin; path<end; ++path){
                    terminal_prices[path]=stochastic_volatility_terminal_price(
                        initial_price,
                        drift,
                        initial_variance,
                        long_term_variance,
                        mean_reversion,
                        volatility_of_variance,
                        time,
                        steps,
                        seed,
                        static_cast<std::uint64_t>(path)
                    );
                }
            });
            begin=end;
        }
        for (auto& worker : workers){
            worker.join();
        }
        return terminal_prices;
    }
}