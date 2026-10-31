cmake_minimum_required(VERSION 3.24)
project(RiskForge
    VERSION 0.1.0
    DESCRIPTION "Risk Simulation Engine"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(CTest)
add_library(riskforge
    src/random/philox.cpp
)
target_compile_features(riskforge
    PUBLIC
        cxx_std_20
)
target_include_directories(riskforge
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMAKELists.txt")
    add_subdirectory(tests)
endif()