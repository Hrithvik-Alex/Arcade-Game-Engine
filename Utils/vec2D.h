//
// Created by Hrithvik  Alex on 2019-12-26.
//

#ifndef UNTITLED_VEC2D_H
#define UNTITLED_VEC2D_H

#include <iostream>

class Vec2D {

public:

    static const Vec2D Zero;

    Vec2D(): Vec2D(0,0){}
    Vec2D(float x, float y): mX(x), mY(y) {}

    inline void SetX(float x){mX = x;}
    inline void SetY(float y){mY = y;}
    inline float GetX() const {return mX;}
    inline float GetY() const {return mY;}

    friend std::ostream& operator<<(std::ostream& cOut, const Vec2D& vec);

    bool operator==(const Vec2D& vec2) const;
    bool operator!=(const Vec2D& vec2) const;

    Vec2D operator-() const;

    Vec2D operator*(float s) const;
    Vec2D operator/(float s) const;
    Vec2D& operator*=(float s);
    Vec2D& operator/=(float s);

    Vec2D operator+(const Vec2D& vec) const;
    Vec2D operator-(const Vec2D& vec) const;
    Vec2D& operator+=(const Vec2D& vec);
    Vec2D& operator-=(const Vec2D& vec);

    float Mag() const;
    float Mag2() const;

    Vec2D GetUnitVec() const;
    Vec2D& Normalize();

    float Distance(const Vec2D& vec) const;
    float Dot(const Vec2D& vec) const;

    Vec2D projectOnto(const Vec2D& vec) const;
    float angleBetween(const Vec2D& vec) const;
    Vec2D reflect(const Vec2D& vec) const;

    void Rotate(float angle, const Vec2D& vec);
    Vec2D RotateResult(float angle, const Vec2D& vec) const;

    friend Vec2D operator*(float s, const Vec2D& vec);

private:
    float mX, mY;

};





#endif //UNTITLED_VEC2D_H
