#ifndef PARAM_H
#define PARAM_H

#include <string>

class Param {
    public:
        Param(int start, int end, int step) : 
        start_(start), end_(end), step_(step), index_(0) {}
        int next();
        int length();
        void reset();
    
    private:
        int start_;
        int end_;
        int step_;
        int index_;
};

#endif // PARAM_H
