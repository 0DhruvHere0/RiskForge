# RiskForge Analytics
Python analtics and API layer for the RiskForge C++ risk engine.
## Install
```bash
cmake --install build/release --prefix build/install
CMAKE_PREFIX_PATH="$PWD/build/install" \
python -m pip install -e 'analytics[dev]'