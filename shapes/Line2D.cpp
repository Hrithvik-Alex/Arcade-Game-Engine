//
// Created by Hrithvik  Alex on 2019-12-27.
//

#include "Line2D.h"
#include "../Utils/utils.h"
#include <cmath>

Line2D::Line2D(): Line2D((Vec2D::Zero),(Vec2D::Zero)) {}

Line2D::Line2D(float x0,float y0,float x1,float y1): p0(Vec2D(x0,y0)), p1(Vec2D(x1,y1)) {}

Line2D::Line2D(const Vec2D& p0, const Vec2D& p1): p0(p0), p1(p1) {}


bool Line2D::operator==(const Line2D& line) const {
    return p0 == line.GetP0() && p1 == line.GetP1();
}


float Line2D::minDistanceFrom(const Vec2D& p, bool isFinite) const {
    return p.Distance(closestPoint(p,isFinite));
}

Vec2D Line2D::closestPoint(const Vec2D& p, bool isFinite) const {
    Vec2D P0toP = p - p0;
    Vec2D P0toP1 = p1 - p0;
    float l2 = P0toP1.Mag2();
    float dot = P0toP.Dot(P0toP1);
    float t = dot/l2;

    if(isFinite) {
        t = std::fmax(0, std::fmin(1.0f, t));
    }

    return p0 + P0toP1*t;
}


Vec2D Line2D::midPoint() const {
    return Vec2D((p0.GetX() + p1.GetX())/2.0f, (p0.GetY() + p1.GetY())/2.0f);
}

float Line2D::Slope() const {
    float run = p1.GetX() - p0.GetX();
    if(fabsf(run) < EPSILON) {
        return 0;
    }

    float rise = p1.GetY() - p0.GetY();
    if(fabsf(rise) < EPSILON) {

    }
    return rise / run;
}

float Line2D::Length() const {
    return p1.Distance(p0);
}