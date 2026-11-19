cmake_minimum_required(VERSION 3.24)
project(
    RiskForge
    VERSION 0.1.0
    DESCRIPTION "Risk Simulation Engine"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(CTest)
find_package(Threads REQUIRED)
add_library(
    riskforge
    src/random/philox.cpp
    src/random/uniform.cpp
    src/random/normal.cpp
    src/simulation/gbm.cpp
    src/simulation/monte_carlo.cpp
    src/simulation/parallel_monte_carlo.cpp
    src/risk/tail.cpp
    src/risk/tail_accumulator.cpp
    src/risk/var.cpp
    src/risk/expected_shortfall.cpp
    src/risk/monte_carlo_risk.cpp
    src/risk/parallel_monte_carlo_risk.cpp
)
target_compile_features(
    riskforge
    PUBLIC
        cxx_std_20
)
target_include_directories(
    riskforge
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_link_libraries(
    riskforge
    PUBLIC
        Threads::Threads
)
if(
    BUILD_TESTING
    AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt"
)
    add_subdirectory(tests)
endif()
if(
    BUILD_TESTING
    AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/CMakeLists.txt"
)
    add_subdirectory(benchmarks)
endif()