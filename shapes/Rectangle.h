//
// Created by Hrithvik  Alex on 2020-03-14.
//

#ifndef LINES_RECTANGLE_H
#define LINES_RECTANGLE_H

#include "Shape.h"

class Rectangle: public Shape {
public:
    Rectangle();
    Rectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
    Rectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

    inline void setTopLeftPoint(const Vec2D& topLeft) { points[0] = topLeft;}
    inline void setBottomRightPoint(const Vec2D& bottomRight) { points[1] = bottomRight;}

    Vec2D getTopLeftPoint() const {return points[0];}
    Vec2D getBottomRightPoint() const {return points[1];}

    float getWidth() const;
    float getHeight() const;

    void MoveTo(const Vec2D& position);

    virtual Vec2D getCenter() const override;

    bool intersects(const Rectangle& otherRect) const;
    bool contains(const Vec2D& point) const;

    static Rectangle inset(const Rectangle& rect, Vec2D& insets);

    virtual std::vector<Vec2D> getPoints() const override;
};


#endif //LINES_RECTANGLE_H
