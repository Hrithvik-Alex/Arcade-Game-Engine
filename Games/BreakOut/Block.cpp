//
// Created by Hrithvik  Alex on 2020-04-12.
//

#include "Block.h"
#include "../../graphics/Screen.h"
#include "Ball.h"

Block::Block(): mOutlineColor(Color::White()), mFillColor(Color::White()), mHp(1) {}

void Block::init(const Rectangle& rect, int hp, const Color& outlineColor, const Color& fillColor) {
    Excluder::init(rect);
    mHp = hp;
    mOutlineColor = outlineColor;
    mFillColor = fillColor;
}

void Block::draw(Screen& screen) {
    screen.Draw(getRectangle(), mOutlineColor, true, mFillColor);
}

void Block::bounce(Ball& ball, const BoundaryEdge& edge) {
    ball.bounce(edge);
}

void Block::reduceHP() {
    if(mHp > 0) {
        --mHp;
    }
}