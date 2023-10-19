#include <vector>
#include <functional>
#include "params.h"

template <std::size_t Size>
class GridSearch {
public:
    GridSearch(const Param[Size]& params) : params_(params) {}
    void search(std::function<int(int[Size])> callback);

private:
    const Param[Size]& params_;
};