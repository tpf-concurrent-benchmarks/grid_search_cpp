# grid_search_cpp

## How to build with CMake

The minimum required version of CMake is 3.11 as per requested in the `CMakeLists.txt` file.
Once in the root directory of the project, run the following commands:

```bash
mkdir cmake-build-debug (or any other name)
cd cmake-build-debug
cmake ..
cmake --build .
```

## How to run

Once the project is built, you can run the executable `grid_search_cpp` with the following command:

```bash
./grid-search-cpp
```

## Used libraries

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [AMQP-CPP](https://github.com/CopernicaMarketingSoftware/AMQP-CPP): C++ library for asynchronous non-blocking communication with RabbitMQ
- [libuv](https://libuv.org/): multi-platform support library with a focus on asynchronous I/O