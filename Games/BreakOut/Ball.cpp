//
// Created by Hrithvik  Alex on 2020-04-10.
//

#include "Ball.h"
#include "../../Utils/utils.h"
#include "../../graphics/Screen.h"
#include "../../shapes/Circle.h"
#include "Boundary.h"


const float Ball::RADIUS = 5.0f;

Ball::Ball(): Ball(Vec2D::Zero, Ball::RADIUS) {}
Ball::Ball(const Vec2D& pos, float radius): mBBox(pos - Vec2D(radius, radius), radius*2.0f, radius*2.0f), mVelocity(Vec2D::Zero) {}

void Ball::update(uint32_t dt) {
    mBBox.MoveBy(mVelocity * MilliSecondsToSeconds(dt));
}

void Ball::draw(Screen& screen) {
    Circle circ = {mBBox.getCenter(), getRadius()};
    screen.Draw(circ, Color::Red(), true, Color::Red());

}

void Ball::makeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge) {
    if (edge.normal == DOWN_DIR) {
        mBBox.MoveTo(Vec2D(mBBox.getTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
    } else if (edge.normal == UP_DIR) {
        mBBox.MoveTo(Vec2D(mBBox.getTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBBox.getHeight()));
    } else if (edge.normal == RIGHT_DIR) {
        mBBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBBox.getTopLeftPoint().GetY()));
    } else if (edge.normal == LEFT_DIR) {
        mBBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() - mBBox.getWidth(), mBBox.getTopLeftPoint().GetY()));
    }

    pointOnEdge = edge.edge.closestPoint(mBBox.getCenter(), limitToEdge);
}

void Ball::bounce(const BoundaryEdge& boundaryEdge) {
   Vec2D pointOnEdge;
   makeFlushWithEdge(boundaryEdge, pointOnEdge, false);
   mVelocity = mVelocity.reflect(boundaryEdge.normal);
}


void Ball::moveTo(const Vec2D& point) {
    mBBox.MoveTo(point - Vec2D(getRadius(),getRadius()));
}