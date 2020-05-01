//
// Created by Hrithvik  Alex on 2020-04-10.
//

#ifndef LINES_BALL_H
#define LINES_BALL_H

#include "../../shapes/Rectangle.h"
#include <stdint.h>

class Screen;
struct BoundaryEdge;

class Ball {
public:
    Ball();
    Ball(const Vec2D& pos, float radius);

    void update(uint32_t dt);
    void draw(Screen& screen);
    void makeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
    inline void stop() {mVelocity = Vec2D::Zero;}
    void moveTo(const Vec2D& point);

    void bounce(const BoundaryEdge& boundaryEdge);

    inline const Rectangle getBoundingRect() const {return mBBox;}
    inline void setVelocity(const Vec2D& vel) {mVelocity = vel;}
    inline Vec2D getVelocity() const { return mVelocity;}
    inline float getRadius() const {return mBBox.getWidth()/2.0f;}
    inline Vec2D getPosition() const {return mBBox.getCenter();}

private:
    Rectangle mBBox;
    Vec2D mVelocity;

    static const float RADIUS;
};


#endif //LINES_BALL_H
