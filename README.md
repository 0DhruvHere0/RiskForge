# RiskForge
RiskForge is a C++20 quantitative risk and simulation engine for Monte Carlo
risk estimation, portfolio analysis, options pricing, advanced stochastic
models, and historical backtesting.
## Current status
- C++ engine: complete
- C++ production hardening: complete
- Python bindings: next
- Rust service: planned
- Web frontend: planned
The C++ test suite currently contains 246 passing tests.
## Main capabilities
- Philox4x32-10 random number generation
- Open-interval uniform generation
- AS241 normal quantiles
- Student-t sampling
- Single-asset and multi-asset GBM
- Parallel Monte Carlo simulation
- Stochastic volatility
- Jump diffusion
- Value at Risk
- Expected Shortfall
- Order-statistic confidence intervals
- Portfolio risk estimation
- Black-Scholes pricing and Greeks
- Implied volatility
- Volatility surfaces
- Historical backtesting
- Stress scenarios
- GBM calibration
- CMake package installation
## Repository structure
```text
RiskForge/
├── include/       Public C++ headers
├── src/           C++ implementation
├── tests/         GoogleTest tests
├── benchmarks/    Google Benchmark programs
├── tools/         Development utilities
├── docs/          Project documentation
├── analytics/     Planned Python layer
└── .github/       Continuous integration
```
## Quick start
```bash
cmake --fresh --preset debug
cmake --build --preset debug --parallel
ctest --preset debug --output-on-failure
```
## Release build
```bash
cmake --fresh --preset release
cmake --build --preset release --parallel
ctest --preset release --output-on-failure
```
## Documentation
- [Build guide](docs/build.md)
- [Installation guide](docs/installation.md)
- [C++ API](docs/cpp-api.md)
- [Testing](docs/testing.md)
- [Benchmarks](docs/benchmarks.md)
- [Phase status](docs/phase-status.md)
- [Design decisions](docs/decisions.md)
## License
License terms should be added before public distribution.