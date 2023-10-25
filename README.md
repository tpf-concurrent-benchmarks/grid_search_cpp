# Grid Search in C++

## How to build with CMake

The minimum required version of CMake is 3.11 as per requested in the `CMakeLists.txt` file.
There are two projects in this repository, one in `src/master` and the other in `src/worker`. Either of them can be built with the 
following commands once you are in the root directory of the project:

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. -DAMQP-CPP_LINUX_TCP=ON
cmake --build .
```

## Running RabbitMQ for development

```bash
docker compose -f=docker-compose-dev.yml up
```

## Running the project

Once one of the projects is built, you can run the executable `worker-gs` (or `worker-gs`) with the following command:

```bash
./worker-gs
```

## Libraries used

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [AMQP-CPP](https://github.com/CopernicaMarketingSoftware/AMQP-CPP): C++ library for asynchronous non-blocking communication with RabbitMQ
- [libuv](https://libuv.org/): multi-platform support library with a focus on asynchronous I/O