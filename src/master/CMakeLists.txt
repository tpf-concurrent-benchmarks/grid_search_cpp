cmake_minimum_required(VERSION 3.25)
project(MasterGridSearch)
add_executable(master-gs src/main.cpp)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_Declare(Statsd URL https://github.com/vthiery/cpp-statsd-client/archive/refs/tags/v2.0.1.tar.gz)
FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)

FetchContent_MakeAvailable(cppzmq)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(Statsd)

add_subdirectory(../shared shared)

target_link_libraries(master-gs PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(master-gs PRIVATE cppzmq)
target_link_libraries(master-gs PUBLIC shared)
target_link_libraries(master-gs PRIVATE cpp-statsd-client)


set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)