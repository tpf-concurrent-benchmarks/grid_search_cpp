cmake_minimum_required(VERSION 3.11)
project(WorkerGridSearch)
add_executable(worker-gs src/main.cpp)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(libzmq URL https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz)
FetchContent_MakeAvailable(libzmq)

FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)
FetchContent_MakeAvailable(cppzmq)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(worker-gs PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(worker-gs PRIVATE cppzmq)

set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

