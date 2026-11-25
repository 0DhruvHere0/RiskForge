cmake_minimum_required(VERSION 3.24)
project(
    RiskForgePython
    VERSION 0.1.0
    LANGUAGES CXX
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(
    Python
    COMPONENTS
        Interpreter
        Development.Module
    REQUIRED
)
find_package(pybind11 CONFIG REQUIRED)
find_package(RiskForge CONFIG REQUIRED)
pybind11_add_module(
    _native
    src/bindings.cpp
)
target_compile_features(
    _native
    PRIVATE
        cxx_std_20
)
target_link_libraries(
    _native
    PRIVATE
        RiskForge::riskforge
)
install(
    TARGETS _native
    LIBRARY DESTINATION riskforge
)