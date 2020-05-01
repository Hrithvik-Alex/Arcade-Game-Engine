//
// Created by Hrithvik  Alex on 2020-04-27.
//

#ifndef LINES_BITMAPFONT_H
#define LINES_BITMAPFONT_H

#include "SpriteSheet.h"
#include "../Utils/utils.h"
#include <stdint.h>

class Vec2D;
class Rectangle;

enum BitmapFontXAlignment {
    BFXA_LEFT = 0,
    BFXA_CENTER,
    BFXA_RIGHT,
};

enum BitmapFontYAlignment {
    BFYA_TOP = 0,
    BFYA_CENTER,
    BFYA_BOTTOM
};

class BitmapFont {
public:

    BitmapFont(){}
    bool load(const std::string& name);
    Size getSizeOf(const std::string& str) const;
    Vec2D getDrawPosition(const std::string& str, const Rectangle& box, BitmapFontXAlignment xAlign = BFXA_LEFT, BitmapFontYAlignment yAlign = BFYA_TOP) const;

    inline const SpriteSheet& getSpriteSheet() const {return mFontSheet;}
    const uint32_t getFontSpacingBetweenLetters() const {return 2;}
    const uint32_t getFontSpacingBetweenWords() const {return 5;}


private:
    SpriteSheet mFontSheet;
};


#endif //LINES_BITMAPFONT_H
