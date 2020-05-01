//
// Created by Hrithvik  Alex on 2020-04-11.
//

#ifndef LINES_LEVELBOUNDARY_H
#define LINES_LEVELBOUNDARY_H

#include "Excluder.h"

class Rectangle;
class Ball;

class LevelBoundary {
public:
    LevelBoundary(){}
    LevelBoundary(const Rectangle& boundary);
    bool hasCollided(const Ball& ball, BoundaryEdge& edge);
    inline const Rectangle& getRectangle() const {return mIncluder.getRectangle();}


private:
    bool hasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
    Excluder mIncluder;
};


#endif //LINES_LEVELBOUNDARY_H
