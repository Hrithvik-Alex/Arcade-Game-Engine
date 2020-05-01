//
// Created by Hrithvik  Alex on 2020-04-10.
//

#ifndef LINES_PADDLE_H
#define LINES_PADDLE_H

#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

enum PaddleDirection {
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
};

class Paddle: public Excluder {
public:

    static const uint32_t PADDLE_WIDTH = 50;
    static const uint32_t PADDLE_HEIGHT = 10;

    void init(const Rectangle& rect, const Rectangle& boundary);

    void update(uint32_t dt, Ball& ball);

    void draw(Screen& screen);

    bool bounce(Ball& ball);

    inline bool isMovingLeft() const {return mDirection == PaddleDirection::LEFT;}
    inline bool isMovingRight() const {return mDirection == PaddleDirection::RIGHT;}

    inline void setMovementDirection(PaddleDirection dir) {mDirection |= dir;}
    inline void unsetMovementDirection(PaddleDirection dir) {mDirection &= ~dir;}
    inline void stopMovement() {mDirection = 0;}

private:
    uint32_t mDirection;
    Rectangle mBoundary;
    const float VELOCITY = 100.0f;
    const float CORNER_BOUNCE = 0.2f;
};


#endif //LINES_PADDLE_H
