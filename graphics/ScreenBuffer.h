//
// Created by Hrithvik  Alex on 2019-12-27.
//

#ifndef LINES_SCREENBUFFER_H
#define LINES_SCREENBUFFER_H

#include <stdint.h>
#include "color.h"

struct SDL_Surface;

class ScreenBuffer {

public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer& sb);
    ~ScreenBuffer();

    ScreenBuffer& operator=(const ScreenBuffer& sb);

    void Init(uint32_t format, uint32_t width, uint32_t height);

    inline SDL_Surface* GetSurface() {return mSurface;}

    void Clear(const Color& c = Color::Black());

    void SetPixel(const Color& c, int x, int y);

private:

    SDL_Surface* mSurface;
    uint32_t GetIndex(int r, int c);

};


#endif //LINES_SCREENBUFFER_H
