# Testing Guide
## Test framework
RiskForge uses GoogleTest and CTest.
## Run the complete Debug suite
```bash
cmake --fresh --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug --output-on-failure --parallel 2
```
## Test categories
- Known-answer random-number tests
- Numerical reference tests
- Boundary tests
- Validation and exception tests
- Deterministic-seed tests
- Serial and parallel consistency tests
- Analytical option-pricing tests
- Historical backtesting tests
- Package-consumer tests
## Sanitizers
AddressSanitizer and UndefinedBehaviorSanitizer are run in GitHub Actions.
```bash
cmake \
    -S . \
    -B build/sanitizers \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTING=ON \
    -DCMAKE_CXX_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build build/sanitizers --parallel 2
ctest --test-dir build/sanitizers --output-on-failure --parallel 2
```
## Coverage acceptance
The deterministic 200-seed coverage test accepts the range 91%–99%.
The recorded 1000-seed offline result is 948 covered seeds out of 1000, or
94.8%.
## Continuous integration
CI verifies:
- Debug build and tests
- Sanitizer build and tests
- Release package installation
- External CMake package consumption