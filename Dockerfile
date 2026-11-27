FROM python:3.13-slim AS builder
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY . .
RUN cmake \
    -S . \
    -B build/docker \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=OFF \
    -DCMAKE_INSTALL_PREFIX=/opt/riskforge
RUN cmake --build build/docker --parallel
RUN cmake --install build/docker
RUN python -m pip install --no-cache-dir \
    pybind11 \
    scikit-build-core
RUN CMAKE_PREFIX_PATH=/opt/riskforge \
    python -m pip wheel \
    analytics \
    --no-deps \
    --wheel-dir /tmp/wheels
FROM python:3.13-slim
WORKDIR /app
COPY --from=builder /tmp/wheels /tmp/wheels
RUN python -m pip install --no-cache-dir /tmp/wheels/*.whl \
    && rm -rf /tmp/wheels
ENV RISKFORGE_ENV=production
ENV RISKFORGE_HOST=0.0.0.0
ENV RISKFORGE_PORT=8000
EXPOSE 8000
CMD ["python", "-m", "riskforge"]