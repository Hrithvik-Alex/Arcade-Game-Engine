//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANGAMEUTILS_H
#define LINES_PACMANGAMEUTILS_H

#include "../../Utils/vec2D.h"
#include <vector>

static const int PACMAN_MOVEMENT_SPEED = 50; // per second


enum PacmanMovement {
    PACMAN_MOVEMENT_NONE = 0,
    PACMAN_MOVEMENT_UP,
    PACMAN_MOVEMENT_LEFT,
    PACMAN_MOVEMENT_DOWN,
    PACMAN_MOVEMENT_RIGHT,
};

Vec2D getMovementVector(PacmanMovement direction);

PacmanMovement getOppositeDirection(PacmanMovement direction);

std::vector<PacmanMovement>  getPerpendicularMovements(PacmanMovement direction);



#endif //LINES_PACMANGAMEUTILS_H
