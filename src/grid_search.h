#include <vector>
#include <functional>
#include "params.h"

template <std::size_t Size>
class GridSearch {
public:
    GridSearch(const Params<Size>& params) : params_(params) {}
    void search(std::function<int(std::array<int, Size>&)> callback);

private:
    const Params<Size>& params_;
};