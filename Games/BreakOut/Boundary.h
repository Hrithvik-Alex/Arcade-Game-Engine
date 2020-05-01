//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_BOUNDARY_H
#define LINES_BOUNDARY_H

#include "../../Utils/vec2D.h"
#include "../../shapes/Line2D.h"

enum EdgeType {
    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUM_EDGES
};


static const Vec2D UP_DIR = {0,-1};
static const Vec2D DOWN_DIR = {0,1};
static const Vec2D LEFT_DIR = {-1,0};
static const Vec2D RIGHT_DIR = {1,0};

struct BoundaryEdge {
    Vec2D normal;
    Line2D edge;
};

#endif //LINES_BOUNDARY_H
