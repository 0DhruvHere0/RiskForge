#include "riskforge/portfolio/parallel_multi_asset_gbm.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include "riskforge/portfolio/correlation.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <thread>
#include <vector>
namespace riskforge::portfolio{
    std::vector<std::vector<double>>
    simulate_multi_asset_gbm_terminal_prices_parallel(
        const MultiAssetGbmConfig& config,
        std::size_t worker_count
    ){
        if (worker_count==0){
            throw std::invalid_argument("worker_count must be greater than zero");
        }
        const std::size_t asset_count= config.initial_prices.size();
        if (asset_count==0 || config.drifts.size()!=asset_count || config.volatilities.size()!=asset_count || config.correlation.size()!=asset_count || config.path_count==0){
            throw std::invalid_argument("invalid multi-asset configuration");
        }
        const Matrix lower= cholesky_decompose(config.correlation);
        const std::size_t thread_count= std::min(worker_count, config.path_count);
        std::vector<std::vector<double>> terminal_prices(
            config.path_count,
            std::vector<double>(asset_count)
        );
        const double square_root_time=
            std::sqrt(config.time);
        const riskforge::random::Philox4x32_10::Key key{
            config.seed,
            config.seed^0x9E3779B9u
        };
        std::vector<std::thread> workers;
        workers.reserve(thread_count);
        const std::size_t block_size= config.path_count/thread_count;
        const std::size_t remainder= config.path_count%thread_count;
        std::size_t begin= 0;
        for (std::size_t worker=0; worker<thread_count; ++worker){
            const std::size_t count= block_size+(worker<remainder ? 1u:0u);
            const std::size_t end= begin+count;
            workers.emplace_back(
                [&,begin,end](){
                    for (std::size_t path=begin; path<end; ++path){
                        const std::uint64_t path_index= static_cast<std::uint64_t>(path);
                        std::vector<double> independent_normals(asset_count);
                        for (std::size_t asset=0; asset<asset_count; ++asset){
                            const riskforge::random::Philox4x32_10::Counter counter{
                                    static_cast<std::uint32_t>(path_index),
                                    static_cast<std::uint32_t>(path_index>>32u),
                                    static_cast<std::uint32_t>(asset),
                                    0u
                                };
                            const auto block=
                                riskforge::random::Philox4x32_10::generate(
                                counter,
                                key
                            );
                            independent_normals[asset]=
                                riskforge::random::normal_ppf(
                                    riskforge::random::uniform_open01(
                                    block[0],
                                    block[1]
                                )
                            );
                        }
                        for (std::size_t asset=0; asset<asset_count; ++asset){
                            double correlated_normal= 0.0;
                            for (std::size_t index=0; index<=asset; ++index){
                                correlated_normal+= lower[asset][index]*independent_normals[index];
                            }
                            const double log_return=
                                (config.drifts[asset] - 0.5 * config.volatilities[asset] * config.volatilities[asset])* config.time + config.volatilities[asset] * square_root_time * correlated_normal;
                            terminal_prices[path][asset]= config.initial_prices[asset] * std::exp(log_return);
                        }
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