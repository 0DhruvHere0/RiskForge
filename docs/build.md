# Build Guide
## Requirements
- CMake 3.24 or newer
- C++20 compiler
- Git
- GoogleTest and Google Benchmark are downloaded by CMake through FetchContent
Supported development environments include macOS with AppleClang and Linux
with a C++20-compatible compiler.
## Debug build
```bash
cmake --fresh --preset debug
cmake --build --preset debug --parallel
ctest --preset debug --output-on-failure
```
To limit local resource usage:
```bash
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure --parallel 2
```
## Release build
```bash
cmake --fresh --preset release
cmake --build --preset release --parallel
ctest --preset release --output-on-failure
```
## Sanitizer build
```bash
cmake \
    --fresh \
    -S . \
    -B build/sanitizers \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTING=ON \
    -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
```
```bash
cmake --build build/sanitizers --parallel 2
ctest --test-dir build/sanitizers --output-on-failure --parallel 2
```
## Coverage utility
```bash
cmake --build --preset debug --target riskforge_coverage_1000 --parallel
./build/debug/riskforge_coverage_1000
```
## Clean rebuild
Use the CMake `--fresh` option instead of manually deleting build files:
```bash
cmake --fresh --preset debug
```
Build directories are ignored by Git and must not be committed.