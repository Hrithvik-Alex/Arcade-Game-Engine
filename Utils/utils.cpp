//
// Created by Hrithvik  Alex on 2019-12-26.
//

#include "utils.h"
#include <cmath>
#include <algorithm>
#include <cctype>

bool IsEqual(float x, float y) {
    return fabsf(x-y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y) {
    return x > y | IsEqual(x,y);
}

bool IsLessThanOrEqual(float x, float y) {
    return x < y | IsEqual(x,y);
}

float MilliSecondsToSeconds(unsigned int milliseconds) {
    return static_cast<float>(milliseconds) / 1000.0f;
}

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c) {
return r * width + c;
}

bool stringCompare(const std::string& a, const std::string& b) {
    if(a.length() == b.length()) {
        return std::equal(b.begin(), b.end(), a.begin(), [](unsigned char a, unsigned char b){
            return std::tolower(a) == std::tolower(b);
        });
    }
    return  false;
}

float Clamp(float val, float min, float max) {
    if(val > max) {
        return max;
    }
    if(val < min) {
        return min;
    }
    return val;
}
