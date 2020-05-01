//
// Created by Hrithvik  Alex on 2019-12-27.
//
#include "ScreenBuffer.h"
#include "SDL.h"
#include <cassert>
#include <iostream>

ScreenBuffer::ScreenBuffer(): mSurface(nullptr) {}
ScreenBuffer::ScreenBuffer(const ScreenBuffer& sb) {

    mSurface = SDL_CreateRGBSurfaceWithFormat(0, sb.mSurface->w, sb.mSurface->h, 0, sb.mSurface->format->format);

    SDL_BlitSurface(sb.mSurface, nullptr, mSurface, nullptr);
}

ScreenBuffer::~ScreenBuffer() {
    if(mSurface) {
        SDL_FreeSurface(mSurface);
    }
}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& sb) {
    if(this == &sb) {
        return *this;
    }

    if(mSurface != nullptr) {
        SDL_FreeSurface(mSurface);
        mSurface = nullptr;
    }

    if(sb.mSurface != nullptr) {
        mSurface = SDL_CreateRGBSurfaceWithFormat(0, sb.mSurface->w, sb.mSurface->h, 0, sb.mSurface->format->format);

        SDL_BlitSurface(sb.mSurface, nullptr, mSurface, nullptr);
    }
    return *this;
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height) {
    mSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
    Clear();
}


void ScreenBuffer::Clear(const Color& c) {
    assert(mSurface);
    if(mSurface) {
        SDL_FillRect(mSurface, nullptr, c.GetPixelColor());
    }
}

void ScreenBuffer::SetPixel(const Color& c, int x, int y) {
    assert(mSurface);
    if(y < mSurface->h & y >= 0 & x < mSurface->w & x >= 0) {
        SDL_LockSurface(mSurface);

        uint32_t *pixels = (uint32_t *) mSurface->pixels;

        uint32_t index = GetIndex(y, x);

        Color surfaceColor = Color(pixels[index]);

        pixels[index] = Color::Evaluate1MinusSourceAlpha(c, surfaceColor).GetPixelColor();
        SDL_UnlockSurface(mSurface);
    }
}

uint32_t ScreenBuffer::GetIndex(int r, int c) {
    assert(mSurface);
    return r * mSurface->w + c;
}
