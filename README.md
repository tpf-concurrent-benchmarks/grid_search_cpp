# grid_search_cpp

## How to build with CMake

The minimum required version of CMake is 3.11 as per requested in the `CMakeLists.txt` file.
Once in the root directory of the project, run the following commands:

```bash
mkdir cmake-build-debug (or any other name)
cd cmake-build-debug
cmake ../
cmake --build .
```

## How to run

Once the project is built, you can run the executable `grid_search_cpp` with the following command:

```bash
./grid-search-cpp
```

### Backup for later

```bash
sudo apt install libboost-all-dev
```