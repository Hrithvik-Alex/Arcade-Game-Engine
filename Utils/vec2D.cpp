//
// Created by Hrithvik  Alex on 2019-12-26.
//
#include "vec2D.h"
#include "utils.h"
#include <cassert>
#include <cmath>

const Vec2D Vec2D::Zero;

std::ostream& operator<<(std::ostream& cOut, const Vec2D& vec) {
    std::cout << "X: " << vec.mX << "     Y: " << vec.mY << std::endl;
    return cOut;
}

Vec2D operator*(float s, const Vec2D& vec) {
    return vec * s;
}


bool Vec2D::operator==(const Vec2D& vec2) const {
    return IsEqual(mX, vec2.mX) & IsEqual(mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D& vec2) const {
    return !(*this==vec2);
}

Vec2D Vec2D::operator-() const {
    return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator*(float s) const {
    return Vec2D(s*mX,s*mY);
}

Vec2D Vec2D::operator/(float s) const {
    assert(fabsf(s) > EPSILON);
    return Vec2D(mX/s,mY/s);
}

Vec2D& Vec2D::operator*=(float s) {
    *this = *this * s;
    return *this;
}

Vec2D& Vec2D::operator/=(float s) {
    assert(fabsf(s) > EPSILON);
    *this = *this / s;
    return *this;
}

Vec2D Vec2D::operator+(const Vec2D& vec) const {
    return Vec2D(mX + vec.mX, mY + vec.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const {
    return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D& Vec2D::operator+=(const Vec2D& vec) {
    *this = *this + vec;
    return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& vec) {
    *this = *this - vec;
    return *this;
}

float Vec2D::Mag() const {
    return sqrt(Mag2());
}

float Vec2D::Mag2() const {
    return mX * mX + mY * mY;
}

Vec2D Vec2D::GetUnitVec() const {
    float mag = Mag();

    if(mag > EPSILON) {
        return *this / Mag();
    } else {
        return Vec2D::Zero;
    }
}

Vec2D& Vec2D::Normalize() {
    float mag = Mag();

    if(mag > EPSILON) {
        *this /= Mag();

    }
    return *this;

}

float Vec2D::Distance(const Vec2D& vec) const {
    return (vec - *this).Mag();
}

float Vec2D::Dot(const Vec2D& vec) const {
    return mX*vec.mX + mY*vec.mY;
}

Vec2D Vec2D::projectOnto(const Vec2D& vec) const {
    float mag2 = vec.Mag();
    if(IsLessThanOrEqual(mag2, EPSILON)) {
        return Vec2D::Zero;
    }
    float dot = Dot(vec);
    return dot * (vec  / mag2);
}

float Vec2D::angleBetween(const Vec2D& vec) const {
    return acosf(GetUnitVec().Dot(vec.GetUnitVec()));
}

Vec2D Vec2D::reflect(const Vec2D& vec) const {
    return (*this - 2 * projectOnto(vec));
}

void Vec2D::Rotate(float angle, const Vec2D& vec) {

    *this = RotateResult(angle,vec);

}

Vec2D Vec2D::RotateResult(float angle, const Vec2D& vec) const {
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);
    thisVec -= vec;
    float xRot = thisVec.mX*cosine - thisVec.mY*sine;
    float yRot = thisVec.mX*sine + thisVec.mY*cosine;

    Vec2D rot = Vec2D(xRot, yRot);
    return rot + vec;
}




