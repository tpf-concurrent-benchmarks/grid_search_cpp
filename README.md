# Grid Search in C++

## How to build with CMake

The minimum required version of CMake is 3.25 as per requested in the `CMakeLists.txt` file.
There are two projects in this repository, one in `src/master` and the other in `src/worker`. Either of them can be built with the 
following commands once you are in the root directory of the desired project:

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Building only the project

If you have already built the project (with its dependencies) and only want to build the executable, run the following command:

```bash
cmake --build .
```

This is particularly useful when you are developing and want to build the project faster, as you don't need to build the dependencies every time.

## Running all services with Docker

```bash
docker compose -f=docker-compose-deploy.yml up
```

## Running only Graphite, Grafana and cAdvisor with Docker

```bash
docker compose -f=docker-compose-graphite.yaml up
```

## Makefile

There is a Makefile in the root directory of the project that can be used to build and run the project

## Running the project

Once one of the projects is built, you can run the executable `worker-gs` (or `master-gs`) with the following command:

```bash
./worker-gs
```

## Used libraries

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [libzmq](https://github.com/zeromq/libzmq): ZeroMQ core engine in C++
- [cppzmq](https://github.com/zeromq/cppzmq): C++ binding for [ZeroMQ](https://zeromq.org/)
