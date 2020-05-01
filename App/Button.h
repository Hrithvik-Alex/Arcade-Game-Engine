//
// Created by Hrithvik  Alex on 2020-04-28.
//

#ifndef LINES_BUTTON_H
#define LINES_BUTTON_H

#include <string>
#include <functional>
#include "../shapes/Rectangle.h"
#include "../graphics/color.h"
#include "../graphics/BitmapFont.h"

class Screen;

class Button {
public:
    using ButtonAction = std::function<void(void)>;

    Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor = Color::White());
    void init(Vec2D topLeft, unsigned int width, unsigned int height);
    void draw(Screen& theScreen);
    void executeAction();

    inline void setButtonText(const std::string& text) {mTitle = text;}
    inline const std::string& getButtonText() const {return mTitle;}
    inline void setHighlighted(bool highlighted) {mHighlighted = highlighted;}
    inline bool getHighlighted() {return  mHighlighted;}
    inline void setButtonAction(Button::ButtonAction action) {mAction = action;}


private:
    const BitmapFont& mBitmapFont;
    std::string mTitle;
    Rectangle mBBox;

    bool mHighlighted;
    ButtonAction mAction;
    Color mHighlightColor;
    Color mTextColor;
};


#endif //LINES_BUTTON_H
