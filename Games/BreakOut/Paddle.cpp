//
// Created by Hrithvik  Alex on 2020-04-10.
//

#include "Paddle.h"
#include "../../graphics/Screen.h"
#include "../../Utils/utils.h"
#include "Boundary.h"
#include "Ball.h"
#include <cassert>

void Paddle::init(const Rectangle& rect, const Rectangle& boundary) {
    Excluder::init(rect);
    mBoundary = boundary;
    mDirection = 0;
}

void Paddle::update(uint32_t dt, Ball& ball) {

    if(getRectangle().contains(ball.getPosition())) {
        Vec2D pointOnEdge;
        ball.makeFlushWithEdge(getEdge(BOTTOM_EDGE), pointOnEdge, true);
    }

    if(mDirection !=0) {
        Vec2D dir;
        if((mDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT && (mDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT) {
            dir = Vec2D::Zero;
        }
        else if(mDirection == PaddleDirection::LEFT) {
            dir = LEFT_DIR;
        } else {
            dir =RIGHT_DIR;
        }

        Vec2D dx = dir * VELOCITY * MilliSecondsToSeconds(dt);
        moveBy(dx);

        const Rectangle& rect = getRectangle();

        if(IsGreaterThanOrEqual(mBoundary.getTopLeftPoint().GetX(), rect.getTopLeftPoint().GetX())) {
            moveTo(Vec2D(mBoundary.getTopLeftPoint().GetX(), rect.getTopLeftPoint().GetY()));
        } else if(IsGreaterThanOrEqual(rect.getBottomRightPoint().GetX(), mBoundary.getBottomRightPoint().GetX())) {
            moveTo(Vec2D(mBoundary.getBottomRightPoint().GetX() - rect.getWidth(), rect.getTopLeftPoint().GetY()));
        }
    }
}

void Paddle::draw(Screen& screen) {
    screen.Draw(getRectangle(), Color::Blue(), true, Color::Blue());
}

bool Paddle::bounce(Ball &ball) {
    BoundaryEdge edge;
    if(hasCollided(ball.getBoundingRect(), edge)) {
        Vec2D pointOnEdge;

        ball.makeFlushWithEdge(edge, pointOnEdge, true);

        if(edge.edge == getEdge(TOP_EDGE).edge) {
            float edgeLength = edge.edge.Length();
            assert(!IsEqual(edgeLength, 0));

            float tx = (pointOnEdge.GetX() - edge.edge.GetP0().GetX())/edgeLength;
            if((tx <= CORNER_BOUNCE && ball.getVelocity().GetX() > 0) || (tx >= (1.0f-CORNER_BOUNCE) && ball.getVelocity().GetX() < 0)) {
                ball.setVelocity(-ball.getVelocity());
                return true;
            }

        }
        ball.setVelocity(ball.getVelocity().reflect(edge.normal));
        return true;
    }
    return false;
}