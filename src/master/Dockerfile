FROM rikorose/gcc-cmake:latest

WORKDIR /app

COPY ./master/resources /app/master/resources
COPY ./master/CMakeLists.txt /app/master/CMakeLists.txt
COPY ./shared /app/shared
COPY ./master/src /app/master/src

RUN cd master; \
    mkdir cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Debug ..; \
    cmake --build .

ENTRYPOINT ["/bin/sh"]