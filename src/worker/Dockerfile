FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./shared /app/shared
COPY ./worker/CMakeLists.txt /app/worker/CMakeLists.txt
COPY ./worker/src /app/worker/src

RUN cd worker; \
    mkdir cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..; \
    cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD ["./app/cmake-build-debug/worker-gs"]