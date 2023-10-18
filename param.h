#ifndef PARAM_H
#define PARAM_H

#include <string>

class Param {
    public:
        Param(int start, int end, int step) : 
        start_(start), end_(end), step_(step), index_(0) {
            length_ = ((end_ - start_) / step_) + 1;
        }
        int next();
        int length();
        void reset();
        bool is_last();
    
    private:
        int start_;
        int end_;
        int step_;
        int index_;
        int length_;
};

#endif // PARAM_H
