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

This is particularly useful when you are local developing and want to build the project faster, as you don't need to build the dependencies every time.

## Running all services with Docker

```bash
docker compose -f=docker-compose-deploy-local.yml up
```

## Running only Graphite, Grafana and cAdvisor with Docker

```bash
docker compose -f=docker-compose-graphite.yaml up
```

## Compile only with Docker

```bash
docker compose up
```

## About ports on worker and master

The default ZMQ ports for the master are 5557 (PUSH) and 5558 (PULL). The ports in the worker must be the same as the ones in the master but interchanged.
For instance, if the master is using 5557 (PUSH) and 5558 (PULL), the worker must use 5558 (PUSH) and 5557 (PULL).

## Number of replicas

If you wish to change the number of replicas, you can do so by changing the `N_WORKERS` constant in the `Makefile` file.

## Makefile

There is a Makefile in the root directory of the project that can be used to build and run the project

- `make build`: builds manager and worker images
- `make deploy`: deploys the manager and worker services locally, alongside with Graphite, Grafana and cAdvisor.
- `make deploy_remote`: deploys (with Docker Swarm) the manager and worker services, alongside with Graphite, Grafana and cAdvisor.
- `make remove`: removes all services (stops the swarm)
- `make full_build_master_local:`  builds the manager locally (it downloads and builds all dependencies, so it may take a while). Same for `make full_build_worker_local`.
- `make build_master_local:` builds the manager locally, useful when doing local development and you already run `make full_build_master_local:`. Same for `make build_worker_local`.
- `make run_master_local:` runs the worker locally. It asumes that the master project has been built. Same for `make run_worker_local`.

## Running the project

Once one of the projects is built, you can run the executable `worker-gs` (or `master-gs`) with the following command
once you are in the `cmake-build-debug `directory:

```bash
./worker-gs
```

## Used libraries

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [libzmq](https://github.com/zeromq/libzmq): ZeroMQ core engine in C++
- [cppzmq](https://github.com/zeromq/cppzmq): C++ binding for [ZeroMQ](https://zeromq.org/)
- [cpp-statsd-client](https://github.com/vthiery/cpp-statsd-client): Statsd client implementation for C++
