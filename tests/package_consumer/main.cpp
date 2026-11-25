#include "riskforge/riskforge.hpp"
#include <string_view>
int main(){
    return std::string_view(riskforge::version())=="0.1.0" ? 0:1;
}