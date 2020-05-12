//
// Created by Hrithvik  Alex on 2020-05-08.
//

#include "PacmanGameUtils.h"

Vec2D getMovementVector(PacmanMovement direction) {
    if(direction == PACMAN_MOVEMENT_LEFT) {
        return Vec2D(-1,0);
    } else if(direction == PACMAN_MOVEMENT_DOWN) {
        return Vec2D(0,1);
    } else if(direction == PACMAN_MOVEMENT_RIGHT) {
        return Vec2D(1,0);
    } else if(direction == PACMAN_MOVEMENT_UP) {
        return Vec2D(0, -1);
    }

    return Vec2D::Zero;
}

PacmanMovement getOppositeDirection(PacmanMovement direction) {
    if(direction == PACMAN_MOVEMENT_LEFT) {
        return PACMAN_MOVEMENT_RIGHT;
    } else if(direction == PACMAN_MOVEMENT_DOWN) {
        return PACMAN_MOVEMENT_UP;
    } else if(direction == PACMAN_MOVEMENT_RIGHT) {
        return PACMAN_MOVEMENT_LEFT;
    } else if(direction == PACMAN_MOVEMENT_UP) {
        return PACMAN_MOVEMENT_DOWN;
    }

    return PACMAN_MOVEMENT_NONE;
}

std::vector<PacmanMovement>  getPerpendicularMovements(PacmanMovement direction) {

    std::vector<PacmanMovement> perpendicularDirections;

    if(direction == PACMAN_MOVEMENT_LEFT || direction == PACMAN_MOVEMENT_RIGHT) {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_UP);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_DOWN);
    } else if(direction == PACMAN_MOVEMENT_DOWN || direction == PACMAN_MOVEMENT_UP) {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_LEFT);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_RIGHT);
    } else if(direction == PACMAN_MOVEMENT_NONE) {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_UP);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_LEFT);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_DOWN);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_RIGHT);
    }

    return perpendicularDirections;
}

std::vector<PacmanMovement> getOtherDirections(PacmanMovement direction) {
    std::vector<PacmanMovement> directions;

    for(int dir = PacmanMovement::PACMAN_MOVEMENT_NONE + 1; dir <= PACMAN_MOVEMENT_RIGHT; ++dir) {
        if(dir != direction) {
            directions.push_back(static_cast<PacmanMovement>(dir));
        }
    }

    return directions;
}