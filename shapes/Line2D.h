//
// Created by Hrithvik  Alex on 2019-12-27.
//

#ifndef LINES_LINE2D_H
#define LINES_LINE2D_H

#include "../Utils/vec2D.h"

class Line2D {
public:

    Line2D();
    Line2D(float x0,float y0,float x1,float y1);
    Line2D(const Vec2D& p0, const Vec2D& p1);

    inline const Vec2D& GetP0() const {return p0;}
    inline const Vec2D& GetP1() const {return p1;}

    inline void SetP0(const Vec2D& vec) {p0 = vec;}
    inline void SetP1(const Vec2D& vec) {p1 = vec;}

    bool operator==(const Line2D& line) const;
    float minDistanceFrom(const Vec2D& p, bool isFinite = false) const;
    Vec2D closestPoint(const Vec2D& p, bool isFinite = false) const;

    Vec2D midPoint() const;
    float Slope() const;
    float Length() const;

private:
    Vec2D p0;
    Vec2D p1;

};


#endif //LINES_LINE2D_H
