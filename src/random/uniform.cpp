#include "riskforge/random/uniform.hpp"
#include <cstdint>
#include <cmath>
namespace riskforge::random {
    double uniform_open01(
        std::uint32_t word0,
        std::uint32_t word1
    ){
        const std::uint64_t bits= (static_cast<std::uint64_t>(word0)<<21)|(static_cast<std::uint64_t>(word1)>>11);
        double value= static_cast<double>(bits) * 0x1.0p-53;
        if (value==0.0){
            value= std::nextafter(0.0, 1.0);
        }
        if (value==1){
            value= std::nextafter(1.0, 0.0);
        }
        return value;
    }
}