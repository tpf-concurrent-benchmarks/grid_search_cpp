# Grid Search in C++

## How to build with CMake

The minimum required version of CMake is 3.11 as per requested in the `CMakeLists.txt` file.
There are two projects in this repository, one in `src/master` and the other in `src/worker`. Either of them can be built with the 
following commands once you are in the root directory of the desired project:

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. -DAMQP-CPP_LINUX_TCP=ON
cmake --build .
```

## Running all services and RabbitMQ with Docker

```bash
docker compose -f=docker-compose.yml up
```

## Running only RabbitMQ with Docker

```bash
docker compose -f=docker-compose-dev.yml up
```

## Makefile

There is a Makefile in the root directory of the project that can be used to build and run the project

## Running the project

Once one of the projects is built, you can run the executable `worker-gs` (or `master-gs`) with the following command:

```bash
./worker-gs
```

## Libraries used

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [libzmq](https://github.com/zeromq/libzmq): ZeroMQ core engine in C++
- [cppzmq](https://github.com/zeromq/cppzmq): C++ binding for [ZeroMQ](https://zeromq.org/)