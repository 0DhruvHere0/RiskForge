# Benchmarks
RiskForge uses Google Benchmark for performance measurements.
## Build benchmark targets
```bash
cmake --fresh --preset release
cmake --build --preset release --target riskforge_benchmark --parallel
cmake --build --preset release --target riskforge_advanced_models_benchmark --parallel
cmake --build --preset release --target riskforge_backtesting_benchmark --parallel
```
## Run benchmarks
```bash
./build/release/benchmarks/riskforge_benchmark \
    --benchmark_min_time=0.1s
```
```bash
./build/release/benchmarks/riskforge_advanced_models_benchmark \
    --benchmark_min_time=0.1s
```
```bash
./build/release/benchmarks/riskforge_backtesting_benchmark \
    --benchmark_min_time=0.1s
```
Parallel benchmarks use real-time measurement where appropriate.
Benchmark values should be recorded on an otherwise idle machine. Debug builds
are useful for correctness but should not be used for final performance claims.
macOS may report unavailable CPU-frequency information or failed thread
affinity. These warnings affect metadata only.
Benchmark values are machine-dependent and should be used for regression
tracking rather than as universal performance guarantees.