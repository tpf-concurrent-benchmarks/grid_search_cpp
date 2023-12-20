FROM gcc:12.3.0 as builder
LABEL stage=build

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./shared /app/shared
COPY ./worker/CMakeLists.txt /app/worker/CMakeLists.txt
COPY ./worker/src /app/worker/src

RUN cd worker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd worker/cmake-build-debug; cmake --build .

FROM ubuntu:22.04

WORKDIR /app

COPY --from=builder /app /app

RUN apt-get update && \
    apt-get install -y software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y gcc-9 && \
    apt-get install -y libstdc++6 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

EXPOSE 5557
EXPOSE 5558

CMD cd /app/worker/cmake-build-debug; ./worker-gs