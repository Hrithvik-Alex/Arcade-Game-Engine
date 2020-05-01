//
// Created by Hrithvik  Alex on 2020-04-27.
//

#include "BitmapFont.h"
#include "../Utils/vec2D.h"
#include "../shapes/Rectangle.h"

bool BitmapFont::load(const std::string& name) {
    return mFontSheet.load(name);
}
Size BitmapFont::getSizeOf(const std::string& str) const {
    Size textSize;
    size_t length = str.length();

    int i = 0;

    for(char c : str) {
        if(c == ' ') {
            textSize.width += getFontSpacingBetweenWords();
            ++i;
            continue;
        }

        Sprite sprite = mFontSheet.getSprite(std::string("") + c);
        textSize.height = textSize.height < sprite.height ? sprite.height : textSize.height;
        textSize.width += sprite.width;

        if(i + 1 < length) {
            textSize.width += getFontSpacingBetweenLetters();
        }
        ++i;

    }

    return textSize;
}

Vec2D BitmapFont::getDrawPosition(const std::string& str, const Rectangle& box, BitmapFontXAlignment xAlign, BitmapFontYAlignment yAlign) const {
    Size textSize = getSizeOf(str);

    uint32_t x = 0;
    uint32_t y = 0;

    if(xAlign == BFXA_CENTER) {
        x = box.getWidth() / 2 - textSize.width / 2;
    } else if(xAlign == BFXA_RIGHT) {
        x = box.getHeight() - textSize.width;
    }

    x += box.getTopLeftPoint().GetX();

    if (yAlign == BFYA_CENTER) {
        y = (box.getHeight() / 2) - textSize.height / 2;
    } else if (yAlign == BFYA_BOTTOM) {
        y = box.getHeight() - textSize.height;
    }

    y += box.getTopLeftPoint().GetY();

    return Vec2D(x,y);

}

