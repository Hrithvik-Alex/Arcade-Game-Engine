//
// Created by Hrithvik  Alex on 2020-04-09.
//

#ifndef LINES_EXCLUDER_H
#define LINES_EXCLUDER_H

#include "../../shapes/Rectangle.h"
#include "Boundary.h"

class Excluder {
public:
    virtual ~Excluder(){}
    void init(const Rectangle& rect, bool reverseNormals = false);
    bool hasCollided(const Rectangle& rect, BoundaryEdge& edge) const;
    Vec2D getCollisionOffset(const Rectangle& rect) const;
    inline const Rectangle& getRectangle() const {return mRect;}
    void moveBy(const Vec2D& delta);
    void moveTo(const Vec2D& point);
    const BoundaryEdge& getEdge(EdgeType edge) const;


private:
    void setupEdges();
    Rectangle mRect;
    BoundaryEdge mEdges[NUM_EDGES];
    bool mReverseNormals;
};


#endif //LINES_EXCLUDER_H
