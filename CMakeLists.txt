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
if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMAKELists.txt")
    add_subdirectory(tests)
endif()