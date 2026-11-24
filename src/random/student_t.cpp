#include "riskforge/random/student_t.hpp"
#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
namespace riskforge::random{
    namespace{
        struct UniformStream{
            Philox4x32_10::Key key;
            std::uint64_t counter;
            std::uint32_t lane;
            double next_uniform(){
                const Philox4x32_10::Counter counter_value{
                    static_cast<std::uint32_t>(counter),
                    static_cast<std::uint32_t>(counter>>32u),
                    lane++,
                    0u
                };
                const auto block=Philox4x32_10::generate(counter_value, key);
                return uniform_open01(block[0], block[1]);
            }
            double next_normal(){
                return normal_ppf(next_uniform());
            }
        };
        double gamma_sample(double shape, UniformStream& stream){
            if (shape<1.0){
                const double sample=gamma_sample(shape+1.0, stream);
                return sample*std::pow(stream.next_uniform(), 1.0/shape);
            }
            const double d=shape-1.0/3.0;
            const double c=1.0/std::sqrt(9.0*d);
            while (true){
                const double normal=stream.next_normal();
                const double transformed=1.0+c*normal;
                if (transformed<=0.0){
                    continue;
                }
                const double cube=transformed*transformed*transformed;
                const double uniform=stream.next_uniform();
                if (uniform<1.0-0.0331*normal*normal*normal*normal){
                    return d*cube;
                }
                if (std::log(uniform)<0.5*normal*normal+d*(1.0-cube+std::log(cube))){
                    return d*cube;
                }
            }
        }
    }
    double student_t_sample(double degrees_of_freedom, std::uint32_t seed, std::uint64_t sample){
        if (!std::isfinite(degrees_of_freedom) || degrees_of_freedom<=0.0){
            throw std::invalid_argument("degrees_of_freedom must be positive and finite");
        }
        UniformStream stream{
            Philox4x32_10::Key{seed, seed^0x9E3779B9u},
            sample,
            0u
        };
        const double normal=stream.next_normal();
        const double chi_squared=2.0*gamma_sample(0.5*degrees_of_freedom, stream);
        return normal/std::sqrt(chi_squared/degrees_of_freedom);
    }
}