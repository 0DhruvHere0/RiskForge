#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <vector>
namespace riskforge::portfolio{
    namespace{
        void validate_config(
            const MultiAssetGbmConfig& config
        ){
            const std::size_t asset_count= config.initial_prices.size();
            if (asset_count==0){
                throw std::invalid_argument("asset configuration must not be empty");
            }
            if (config.drifts.size()!=asset_count || config.volatilities.size()!=asset_count){
                throw std::invalid_argument("asset parameters must have equal sizes");
            }
            if (config.correlation.size()!=asset_count){
                throw std::invalid_argument("correlation dimension must match assets");
            }
            if (!std::isfinite(config.time) || config.time<0.0){
                throw std::invalid_argument("time must be non-negative and finite");
            }
            if (config.path_count==0){
                throw std::invalid_argument("path_count must be greater than zero");
            }
            for (std::size_t asset=0; asset<asset_count; ++asset){
                if (!std::isfinite(config.initial_prices[asset]) || config.initial_prices[asset]<=0.0){
                    throw std::invalid_argument("initial prices must be positive and finite");
                }
                if (!std::isfinite(config.drifts[asset])){
                    throw std::invalid_argument("drifts must be finite");
                }
                if (!std::isfinite(config.volatilities[asset]) || config.volatilities[asset]<0.0){
                    throw std::invalid_argument("volatilities must be non-negative and finite");
                }
            }
        }
    }
    std::vector<std::vector<double>>
    simulate_multi_asset_gbm_terminal_prices(
        const MultiAssetGbmConfig& config
    ){
        validate_config(config);
        const Matrix lower= cholesky_decompose(config.correlation);
        const std::size_t asset_count= config.initial_prices.size();
        const double square_root_time= std::sqrt(config.time);
        const riskforge::random::Philox4x32_10::Key key{
            config.seed,
            config.seed^0x9E3779B9u
        };
        std::vector<std::vector<double>> terminal_prices(
            config.path_count,
            std::vector<double>(asset_count)
        );
        for (std::size_t path=0; path<config.path_count; ++path){
            const std::uint64_t path_index= static_cast<std::uint64_t>(path);
            std::vector<double> independent_normals(asset_count);
            for (std::size_t asset=0; asset<asset_count; ++asset){
                const riskforge::random::Philox4x32_10::Counter
                    counter{
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
                const double uniform=
                    riskforge::random::uniform_open01(
                        block[0],
                        block[1]
                    );
                independent_normals[asset]= riskforge::random::normal_ppf(uniform);
            }
            for (std::size_t asset=0; asset<asset_count; ++asset){
                double correlated_normal= 0.0;
                for (std::size_t index=0; index<=asset; ++index){
                    correlated_normal+= lower[asset][index]* independent_normals[index];
                }
                const double log_return=
                    (
                        config.drifts[asset]- 0.5 * config.volatilities[asset] * config.volatilities[asset]
                    )*
                    config.time+ config.volatilities[asset]* square_root_time* correlated_normal;
                terminal_prices[path][asset]= config.initial_prices[asset]* std::exp(log_return);
            }
        }
        return terminal_prices;
    }
}