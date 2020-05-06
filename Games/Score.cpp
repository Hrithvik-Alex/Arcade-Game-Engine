//
// Created by Hrithvik  Alex on 2020-05-06.
//

#include "Score.h"
#include "../graphics/Screen.h"
#include <string>

Score::Score(Rectangle rect, const BitmapFont& bitmapFont): mScore(0), mBitmapFont(bitmapFont), mBBox(rect) {}

void Score::draw(Screen& screen) {
    std::string scoreString = std::to_string(mScore);
    screen.Draw(mBitmapFont, scoreString, mBitmapFont.getDrawPosition(scoreString, mBBox, BFXA_CENTER, BFYA_CENTER), Color::White());
}