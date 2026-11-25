cmake_minimum_required(VERSION 3.24)
project(
    RiskForgePackageConsumer
    LANGUAGES CXX
)
find_package(RiskForge CONFIG REQUIRED)
add_executable(
    riskforge_package_consumer
    main.cpp
)
target_compile_features(
    riskforge_package_consumer
    PRIVATE
        cxx_std_20
)
target_link_libraries(
    riskforge_package_consumer
    PRIVATE
        RiskForge::riskforge
)