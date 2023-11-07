FROM rikorose/gcc-cmake:latest

WORKDIR /app

COPY ./shared /app/shared
COPY ./worker/CMakeLists.txt /app/worker/CMakeLists.txt
COPY ./worker/src /app/worker/src

RUN cd worker; \
    mkdir cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..; \
    cmake --build .

ENTRYPOINT ["/bin/sh"]