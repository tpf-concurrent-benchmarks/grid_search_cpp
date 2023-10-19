cmake_minimum_required(VERSION 3.11)
project(GridSearchCpp)
add_executable(grid-search-cpp src/main.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(grid-search-cpp PRIVATE nlohmann_json::nlohmann_json)

set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)