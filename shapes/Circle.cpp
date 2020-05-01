//
// Created by Hrithvik  Alex on 2020-04-05.
//

#include "Circle.h"
#include "../Utils/utils.h"


Circle::Circle(): Circle(Vec2D::Zero, 0) {}

Circle::Circle(const Vec2D& center, float r) {
    points.push_back(center);
    radius = r;
}


bool Circle::intersects(const Circle& circle) const {
    return getCenter().Distance(circle.getCenter()) < radius + circle.radius;
}
bool Circle::contains(const Vec2D& point) const {
    return IsLessThanOrEqual(getCenter().Distance(point), radius);
}
