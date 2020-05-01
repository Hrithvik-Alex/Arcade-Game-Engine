//
// Created by Hrithvik  Alex on 2020-04-27.
//

#ifndef LINES_SPRITESHEET_H
#define LINES_SPRITESHEET_H

#include "BMPImage.h"
#include <string>
#include <vector>
#include <stdint.h>

struct Sprite {
    uint32_t xPos = 0;
    uint32_t yPos = 0;
    uint32_t width = 0;
    uint32_t height = 0;
};

class SpriteSheet {
public:

    SpriteSheet();
    bool load(const std::string& name);
    Sprite getSprite(const std::string& spriteName) const;

    std::vector<std::string> spriteNames() const;

    inline const BMPImage& getBMPImage() const {return mBMPImage;}
    inline uint32_t getWidth() const {return mBMPImage.getWidth();}
    inline uint32_t getHeight() const {return mBMPImage.getHeight();}

private:

    bool loadSpriteSections(const std::string& path);

    struct BMPImageSection {
        std::string key = "";
        Sprite sprite;
    };
    BMPImage mBMPImage;
    std::vector<BMPImageSection> mSections;
};


#endif //LINES_SPRITESHEET_H
