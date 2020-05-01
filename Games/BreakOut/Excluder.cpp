//
// Created by Hrithvik  Alex on 2020-04-09.
//

#include "Excluder.h"
#include "../../Utils/utils.h"
#include <cmath>
#include <cassert>

void Excluder::init(const Rectangle& rect, bool reverseNormals) {
    mRect = rect;
    mReverseNormals = reverseNormals;
    setupEdges();
}

bool Excluder::hasCollided(const Rectangle& rect, BoundaryEdge& edge) const {
    if(mRect.intersects(rect)) {
        float yMin = mRect.getTopLeftPoint().GetY() >= rect.getTopLeftPoint().GetY() ? mRect.getTopLeftPoint().GetY() : rect.getTopLeftPoint().GetY();
        float yMax = mRect.getBottomRightPoint().GetY() <= rect.getBottomRightPoint().GetY() ? mRect.getBottomRightPoint().GetY() : rect.getBottomRightPoint().GetY();

        float ySize = yMax - yMin;

        float xMin = mRect.getTopLeftPoint().GetX() >= rect.getTopLeftPoint().GetX() ? mRect.getTopLeftPoint().GetX() : rect.getTopLeftPoint().GetX();
        float xMax = mRect.getBottomRightPoint().GetX() <= rect.getBottomRightPoint().GetX() ? mRect.getBottomRightPoint().GetX() : rect.getBottomRightPoint().GetX();

        float xSize = xMax - xMin;

        if(xSize > ySize) {
            if(rect.getCenter().GetY() > mRect.getCenter().GetY()) {
                edge = mEdges[BOTTOM_EDGE];
            } else {
                edge = mEdges[TOP_EDGE];
            }
        } else {
            if(rect.getCenter().GetX() < mRect.getCenter().GetX()) {
                edge = mEdges[LEFT_EDGE];
            } else {
                edge = mEdges[RIGHT_EDGE];
            }
        }
        return true;
    }

    return false;
}

Vec2D Excluder::getCollisionOffset(const Rectangle& rect) const {
    BoundaryEdge edge;
    Vec2D offset = Vec2D::Zero;
    if(hasCollided(rect, edge)) {
        float yMin = mRect.getTopLeftPoint().GetY() >= rect.getTopLeftPoint().GetY() ? mRect.getTopLeftPoint().GetY() : rect.getTopLeftPoint().GetY();
        float yMax = mRect.getBottomRightPoint().GetY() <= rect.getBottomRightPoint().GetY() ? mRect.getBottomRightPoint().GetY() : rect.getBottomRightPoint().GetY();

        float ySize = yMax - yMin;

        float xMin = mRect.getTopLeftPoint().GetX() >= rect.getTopLeftPoint().GetX() ? mRect.getTopLeftPoint().GetX() : rect.getTopLeftPoint().GetX();
        float xMax = mRect.getBottomRightPoint().GetX() <= rect.getBottomRightPoint().GetX() ? mRect.getBottomRightPoint().GetX() : rect.getBottomRightPoint().GetX();

        float xSize = xMax - xMin;

        if(!IsEqual(edge.normal.GetY(), 0)) {
            offset = (ySize + 1) * edge.normal;
        } else {
            offset = (xSize + 1) * edge.normal;
        }
    }

    return offset;

}

void Excluder::moveBy(const Vec2D& delta) {
    mRect.MoveBy(delta);
    setupEdges();
}

void Excluder::moveTo(const Vec2D& point) {
    mRect.MoveTo(point);
    setupEdges();
}

const BoundaryEdge& Excluder::getEdge(EdgeType edge) const {
    assert(edge != NUM_EDGES);
    return mEdges[edge];
}

void Excluder::setupEdges() {
    mEdges[TOP_EDGE].edge = {mRect.getTopLeftPoint().GetX(), mRect.getTopLeftPoint().GetY(), mRect.getBottomRightPoint().GetX(), mRect.getTopLeftPoint().GetY()};
    mEdges[TOP_EDGE].normal = UP_DIR;

    mEdges[LEFT_EDGE].edge = {mRect.getTopLeftPoint().GetX(), mRect.getTopLeftPoint().GetY(), mRect.getTopLeftPoint().GetX(), mRect.getBottomRightPoint().GetY()};
    mEdges[LEFT_EDGE].normal = LEFT_DIR;

    mEdges[BOTTOM_EDGE].edge = {mRect.getTopLeftPoint().GetX(), mRect.getBottomRightPoint().GetY(),  mRect.getBottomRightPoint().GetX(), mRect.getBottomRightPoint().GetY()};
    mEdges[BOTTOM_EDGE].normal = DOWN_DIR;

    mEdges[RIGHT_EDGE].edge = {mRect.getBottomRightPoint().GetX(), mRect.getBottomRightPoint().GetY(), mRect.getBottomRightPoint().GetX(), mRect.getTopLeftPoint().GetY()};
    mEdges[RIGHT_EDGE].normal = RIGHT_DIR;

    if(mReverseNormals) {
        for (auto& edge : mEdges) {
            edge.normal = -edge.normal;
        }
    }
}