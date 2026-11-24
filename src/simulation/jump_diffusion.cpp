#include "riskforge/simulation/jump_diffusion.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
namespace riskforge::simulation{
    namespace{
        struct PhiloxStream{
            riskforge::random::Philox4x32_10::Key key;
            std::uint64_t sample;
            std::uint32_t lane;
            double next_uniform(){
                const riskforge::random::Philox4x32_10::Counter counter{
                    static_cast<std::uint32_t>(sample),
                    static_cast<std::uint32_t>(sample>>32u),
                    lane++,
                    0u
                };
                const auto block=riskforge::random::Philox4x32_10::generate(counter, key);
                return riskforge::random::uniform_open01(block[0], block[1]);
            }
            double next_normal(){
                return riskforge::random::normal_ppf(next_uniform());
            }
        };
        std::uint64_t poisson_sample(double mean, PhiloxStream& stream){
            if (mean==0.0){
                return 0u;
            }
            const double uniform=stream.next_uniform();
            double probability=std::exp(-mean);
            double cumulative=probability;
            std::uint64_t count=0u;
            while (uniform>cumulative){
                ++count;
                probability*=mean/static_cast<double>(count);
                cumulative+=probability;
            }
            return count;
        }
    }
    double jump_diffusion_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double jump_intensity,
        double jump_mean,
        double jump_volatility,
        double time,
        std::uint32_t seed,
        std::uint64_t sample
    ){
        if (!std::isfinite(initial_price) || initial_price<=0.0){
            throw std::invalid_argument("initial_price must be positive and finite");
        }
        if (!std::isfinite(drift)){
            throw std::invalid_argument("drift must be finite");
        }
        if (!std::isfinite(volatility) || volatility<0.0){
            throw std::invalid_argument("volatility must be non-negative and finite");
        }
        if (!std::isfinite(jump_intensity) || jump_intensity<0.0){
            throw std::invalid_argument("jump_intensity must be non-negative and finite");
        }
        if (!std::isfinite(jump_mean)){
            throw std::invalid_argument("jump_mean must be finite");
        }
        if (!std::isfinite(jump_volatility) || jump_volatility<0.0){
            throw std::invalid_argument("jump_volatility must be non-negative and finite");
        }
        if (!std::isfinite(time) || time<0.0){
            throw std::invalid_argument("time must be non-negative and finite");
        }
        PhiloxStream stream{
            riskforge::random::Philox4x32_10::Key{
                seed,
                seed^0x9E3779B9u
            },
            sample,
            0u
        };
        const double diffusion=stream.next_normal();
        const std::uint64_t jump_count=poisson_sample(jump_intensity*time, stream);
        double jump_sum=0.0;
        for (std::uint64_t jump=0u; jump<jump_count; ++jump){
            jump_sum+=jump_mean+jump_volatility*stream.next_normal();
        }
        const double jump_compensation=std::exp(jump_mean+0.5*jump_volatility*jump_volatility)-1.0;
        const double log_return=(drift-0.5*volatility*volatility-jump_intensity*jump_compensation)*time+volatility*std::sqrt(time)*diffusion+jump_sum;
        return initial_price*std::exp(log_return);
    }
}