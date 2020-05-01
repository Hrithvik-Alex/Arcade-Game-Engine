//
// Created by Hrithvik  Alex on 2020-04-11.
//

#include "LevelBoundary.h"
#include "Ball.h"

LevelBoundary::LevelBoundary(const Rectangle& boundary) {
    mIncluder.init(boundary, true);
}

bool LevelBoundary::hasCollided(const Ball& ball, BoundaryEdge& edge) {
    for(int i = 0; i < NUM_EDGES; ++i) {
        BoundaryEdge collisionEdge = mIncluder.getEdge(static_cast<EdgeType>(i));
        if(hasCollidedWithEdge(ball, collisionEdge)) {
            edge = collisionEdge;
            return true;
        }
    }
    return false;
}

bool LevelBoundary::hasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const {
    return  edge.edge.minDistanceFrom(ball.getPosition()) < ball.getRadius();
}