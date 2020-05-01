//
// Created by Hrithvik  Alex on 2020-04-28.
//

#include "Button.h"
#include "../graphics/Screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
  mBitmapFont(bitmapFont), mTextColor(textColor), mHighlightColor(highlightColor), mTitle(""), mHighlighted(false), mAction(nullptr)
{}

void Button::init(Vec2D topLeft, unsigned int width, unsigned int height) {
    mBBox = Rectangle(topLeft, width, height);
}

void Button::draw(Screen& theScreen) {
    theScreen.Draw(mBitmapFont, mTitle, mBitmapFont.getDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);

    if(mHighlighted) {
        theScreen.Draw(mBBox, mHighlightColor);
    }
}

void Button::executeAction() {
    mAction();
}