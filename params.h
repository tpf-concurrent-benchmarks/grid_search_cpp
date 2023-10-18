#include <cstddef>
#include <array>

template <std::size_t Size>
class Params {
    public:
        Params(std::array<int, Size>& start, std::array<int, Size>& end, std::array<int, Size>& step) : 
        start_(start), end_(end), step_(step) {}
        std::array<int, Size>& get_current() { return current_; }
        void next();
        int get_total_iterations();

    
    private:
        std::array<int, Size>& start_;
        std::array<int, Size>& end_;
        std::array<int, Size>& step_;
        std::array<int, Size> current_;
        int total_iterations;
};

