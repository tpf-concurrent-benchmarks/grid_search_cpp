#include <vector>
#include <functional>
#include "param.h"

template<typename T>
class GridSearch {
public:
    GridSearch(std::vector<Param> params) : params_(params) {}

    void search(std::function<void(T)> callback);

private:
    std::vector<Param> params_;
};