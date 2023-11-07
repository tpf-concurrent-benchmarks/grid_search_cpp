FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./master/resources /app/master/resources
COPY ./master/CMakeLists.txt /app/master/CMakeLists.txt
COPY ./shared /app/shared
COPY ./master/src /app/master/src

RUN cd master; \
    mkdir cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..; \
    cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/master/cmake-build-debug; ./master-gs