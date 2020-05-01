//
// Created by Hrithvik  Alex on 2020-04-05.
//

#ifndef LINES_CIRCLE_H
#define LINES_CIRCLE_H

#include "Shape.h"


class Circle: public Shape {
public:
    Circle();
    Circle(const Vec2D& center, float radius);

    virtual Vec2D getCenter() const override {return points[0];}
    inline float getRadius() const {return radius;}
    inline void setRadius(float r) {radius = r;}
    void moveTo(const Vec2D& pos) {points[0] = pos;}
    void moveBy(const Vec2D& pos) {points[0] = Vec2D(points[0].GetX() + pos.GetX(), points[0].GetY() + pos.GetY());}

    bool intersects(const Circle& circle) const;
    bool contains(const Vec2D& point) const;

private:
    float radius;

};


#endif //LINES_CIRCLE_H
