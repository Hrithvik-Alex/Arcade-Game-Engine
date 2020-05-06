//
// Created by Hrithvik  Alex on 2019-12-26.
//

#ifndef UNTITLED_UTILS_H
#define UNTITLED_UTILS_H

#include <string>

class Vec2D;

static const float EPSILON = 0.000001f;

const float PI = 3.141569f;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MilliSecondsToSeconds(unsigned int milliseconds);

unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c);

bool stringCompare(const std::string& a, const std::string& b);

float Clamp(float val, float min, float max);

bool outOfBounds(const Vec2D& vec);

struct Size {
    unsigned int width = 0, height = 0;
};

#endif //UNTITLED_UTILS_H
