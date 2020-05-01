//
// Created by Hrithvik  Alex on 2019-12-28.
//

#ifndef LINES_TRIANGLE_H
#define LINES_TRIANGLE_H

#include "Shape.h"

class Triangle: public Shape {
public:
    Triangle();
    Triangle(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2);

    inline void setP0(const Vec2D& p) {points[0] = p;}
    inline void setP1(const Vec2D& p) {points[1] = p;}
    inline void setP2(const Vec2D& p) {points[2] = p;}

    inline Vec2D getP0() const {return points[0];}
    inline Vec2D getP1() const {return points[1];}
    inline Vec2D getP2() const {return points[2];}

    virtual Vec2D getCenter() const override;

    float Area() const;

    bool contains(const Vec2D& p) const;

private:
    float Area(const Vec2D& p0, const Vec2D& p1, const Vec2D& p2) const;

};

#endif //LINES_TRIANGLE_H
