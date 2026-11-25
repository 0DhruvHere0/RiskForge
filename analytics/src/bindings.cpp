#include "riskforge/version.hpp"
#include <pybind11/pybind11.h>
namespace py=pybind11;
PYBIND11_MODULE(_native, module){
    module.doc()="Python bindings for the RiskForge C++ engine";
    module.def("version", &riskforge::version);
}