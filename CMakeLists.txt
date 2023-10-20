cmake_minimum_required(VERSION 3.11)
project(GridSearchCpp)
add_executable(grid-search-cpp src/main.cpp)

include(FetchContent)

FetchContent_Declare(libuv URL https://github.com/libuv/libuv/archive/refs/tags/v1.46.0.tar.gz)
FetchContent_MakeAvailable(libuv)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
FetchContent_Declare(Amqpcpp URL https://github.com/CopernicaMarketingSoftware/AMQP-CPP/archive/refs/tags/v4.3.26.tar.gz)
FetchContent_MakeAvailable(Amqpcpp)

target_link_libraries(grid-search-cpp PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(grid-search-cpp PRIVATE amqpcpp)
target_link_libraries(grid-search-cpp PRIVATE uv_a)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(grid-search-cpp PRIVATE Threads::Threads)
target_link_libraries(grid-search-cpp PRIVATE dl)

set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)