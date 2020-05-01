//
// Created by Hrithvik  Alex on 2019-12-28.
//

#ifndef LINES_SHAPE_H
#define LINES_SHAPE_H

#include "../Utils/vec2D.h"
#include <vector>

class Shape {
public:
    virtual Vec2D getCenter() const = 0;
    virtual ~Shape() {}
    inline virtual std::vector<Vec2D> getPoints() const {return points;}
    void MoveBy(const Vec2D& delta);

protected:
    std::vector<Vec2D> points;

};

#endif //LINES_SHAPE_H
