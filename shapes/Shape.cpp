//
// Created by Hrithvik  Alex on 2019-12-28.
//

#include "Shape.h"

void Shape::MoveBy(const Vec2D& delta) {
    for(Vec2D& vec : points) {
        vec += delta;
    }
}