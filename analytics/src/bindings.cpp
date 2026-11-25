#include "riskforge/random/normal.hpp"
#include "riskforge/simulation/gbm.hpp"
#include "riskforge/version.hpp"
#include <pybind11/pybind11.h>
namespace py=pybind11;
PYBIND11_MODULE(_native, module){
    module.doc()="Python bindings for the RiskForge C++ engine";
    module.def("version", &riskforge::version);
    module.def(
        "gbm_terminal_price",
        &riskforge::simulation::gbm_terminal_price,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("standard_normal")
    );
}