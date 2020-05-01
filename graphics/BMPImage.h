//
// Created by Hrithvik  Alex on 2020-04-27.
//

#ifndef LINES_BMPIMAGE_H
#define LINES_BMPIMAGE_H

#include "color.h"
#include <vector>
#include <string>
#include <stdint.h>


class BMPImage {
public:

    BMPImage();
    bool load(const std::string& path);

    inline const std::vector<Color>& getPixels() const {return mPixels;}

    inline const uint32_t getWidth() const {return mWidth;}
    inline const uint32_t getHeight() const {return mHeight;}

private:

    std::vector<Color> mPixels;
    uint32_t mWidth;
    uint32_t mHeight;
};


#endif //LINES_BMPIMAGE_H
