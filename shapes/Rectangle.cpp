
#include "Rectangle.h"
#include "../Utils/utils.h"
#include <cmath>

Rectangle::Rectangle(): Rectangle(Vec2D::Zero, Vec2D::Zero) {}


Rectangle::Rectangle(const Vec2D& topLeft, unsigned int width, unsigned int height) {
    points.push_back(topLeft);
    points.push_back(Vec2D(topLeft.GetX()+width-1,topLeft.GetY() + height - 1));
}
Rectangle::Rectangle(const Vec2D& topLeft, const Vec2D& bottomRight) {
    points.push_back(topLeft);
    points.push_back(bottomRight);
}

float Rectangle::getWidth() const {
    return getBottomRightPoint().GetX() - getTopLeftPoint().GetX() + 1;
}

float Rectangle::getHeight() const {
    return  getBottomRightPoint().GetY() - getTopLeftPoint().GetY()  + 1;
}

void Rectangle::MoveTo(const Vec2D& position) {
    float width = getWidth();
    float height = getHeight();

    setTopLeftPoint(position);
    setBottomRightPoint(Vec2D(position.GetX() + width - 1, position.GetY() + height - 1));
}

 Vec2D Rectangle::getCenter() const {
    return Vec2D(getTopLeftPoint().GetX() + getWidth()/2.0f, getTopLeftPoint().GetY() + getHeight()/2.0f);
}

bool Rectangle::intersects(const Rectangle& otherRect) const {
    return !(otherRect.getBottomRightPoint().GetX() < getTopLeftPoint().GetX()
    || otherRect.getTopLeftPoint().GetX() > getBottomRightPoint().GetX()
    || otherRect.getBottomRightPoint().GetY() < getTopLeftPoint().GetY()
    || otherRect.getTopLeftPoint().GetY() > getBottomRightPoint().GetY());
}

bool Rectangle::contains(const Vec2D& point) const {
    bool withinX = point.GetX() >= getTopLeftPoint().GetX() && point.GetX() <= getBottomRightPoint().GetX();
    bool withinY = point.GetY() >= getTopLeftPoint().GetY() && point.GetY() <= getBottomRightPoint().GetY();
    return withinX && withinY;
}

Rectangle Rectangle::inset(const Rectangle& rect, Vec2D& insets) {
    return Rectangle(rect.getTopLeftPoint() + insets, Vec2D(rect.getWidth() - 2*insets.GetX(), rect.getHeight() - 2*insets.GetY()));
}

std::vector<Vec2D> Rectangle::getPoints() const {
    std::vector<Vec2D> allPoints;

    allPoints.push_back(points[0]);
    allPoints.push_back(Vec2D(points[1].GetX(), points[0].GetY()));
    allPoints.push_back(points[1]);
    allPoints.push_back(Vec2D(points[0].GetX(), points[1].GetY()));

    return allPoints;
}