#ifndef PARAMS_H
#define PARAMS_H

#include <cstddef>
#include <array>

template <std::size_t Size>
class Params {
    public:
        Params(std::array<int, Size>& start, std::array<int, Size>& end, std::array<int, Size>& step);
        std::array<int, Size>& get_current();
        void next();
        int get_total_iterations();

    
    private:
        std::array<int, Size>& start_;
        std::array<int, Size>& end_;
        std::array<int, Size>& step_;
        std::array<int, Size> current_;
        int total_iterations;
};

#include "params.cpp"
//should work without this line, but it doesn't in my computer

#endif // PARAMS_H
