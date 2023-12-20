FROM gcc:12.3.0 as builder
LABEL stage=builder

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./master/resources /app/master/resources
COPY ./master/CMakeLists.txt /app/master/CMakeLists.txt
COPY ./shared /app/shared
COPY ./master/src /app/master/src

RUN cd master; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd master/cmake-build-debug; cmake --build .

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

CMD cd /app/master/cmake-build-debug; ./master-gs