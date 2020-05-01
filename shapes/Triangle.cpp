//
// Created by Hrithvik  Alex on 2019-12-28.
//

#include "Triangle.h"
#include <cmath>
#include "../Utils/utils.h"

Triangle::Triangle(): Triangle(Vec2D::Zero, Vec2D::Zero, Vec2D::Zero) {}

Triangle::Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) {
    points.push_back(p0);
    points.push_back(p1);
    points.push_back(p2);
}


 Vec2D Triangle::getCenter() const {
    return Vec2D((points[0].GetX() + points[1].GetX() + points[2].GetX())/3,
                 (points[0].GetY() + points[1].GetY() + points[2].GetY())/3);
}

float Triangle::Area() const {
    return Area(getP0(),getP1(),getP2());
}

bool Triangle::contains(const Vec2D& p) const {
    float a = Area();
    float b = Area(p,points[1],points[2]) + Area(points[0],p,points[2]) + Area(points[0],points[1],p);
    return IsEqual(a,b);
}


float Triangle::Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const {
    return fabsf((p0.GetX() * (p1.GetY() - p2.GetY())
    + p1.GetX()*(p2.GetY() - p0.GetY())
    + p2.GetX()*(p0.GetY() - p1.GetY()))/2.0f);
}