# Installation Guide
RiskForge can be installed as a CMake package.
## Build and install
```bash
cmake --fresh --preset release
cmake --build --preset release --parallel
cmake --install build/release --prefix build/install
```
The installation contains:
- `libriskforge.a`
- Public headers under `include/riskforge`
- CMake package files under `lib/cmake/RiskForge`
## Consume from another CMake project
```cmake
cmake_minimum_required(VERSION 3.24)
project(RiskForgeConsumer LANGUAGES CXX)
find_package(RiskForge CONFIG REQUIRED)
add_executable(consumer main.cpp)
target_compile_features(consumer PRIVATE cxx_std_20)
target_link_libraries(consumer PRIVATE RiskForge::riskforge)
```
Configure the consumer with:
```bash
cmake \
    -S . \
    -B build/consumer \
    -DCMAKE_PREFIX_PATH="$PWD/build/install" \
    -DCMAKE_BUILD_TYPE=Release
```
Build it with:
```bash
cmake --build build/consumer --parallel 2
```
The repository contains a package-consumer verification project at:
```text
tests/package_consumer/
```
## Installed package files
The generated package files are:
```text
build/install/lib/cmake/RiskForge/
├── RiskForgeConfig.cmake
├── RiskForgeConfigVersion.cmake
├── RiskForgeTargets.cmake
└── RiskForgeTargets-release.cmake
```
Build directories and local installation directories are development artifacts
and should not be committed.