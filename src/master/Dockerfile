FROM gcc:12.3.0 as builder
LABEL stage=builder

RUN apt-get update; \
    apt-get install -y cmake libzmq3-dev

WORKDIR /app

COPY ./master/resources /app/master/resources
COPY ./master/CMakeLists.txt /app/master/CMakeLists.txt
COPY ./shared /app/shared
COPY ./master/src /app/master/src

RUN cd master; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCPPZMQ_BUILD_TESTS=OFF -D BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ..

RUN cd master/cmake-build-debug; cmake --build .

FROM alpine:latest

WORKDIR /app

RUN apk update && apk add --no-cache gcompat libzmq

COPY --from=builder /app /app

EXPOSE 5557
EXPOSE 5558

CMD cd /app/master/cmake-build-debug; ./master-gs