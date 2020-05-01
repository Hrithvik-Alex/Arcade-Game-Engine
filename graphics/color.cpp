//
// Created by Hrithvik  Alex on 2019-12-27.
//
#include "color.h"
#include "SDL.h"
#include <iostream>

const SDL_PixelFormat* Color::mFormat = nullptr;

void Color::InitColorFormat(const SDL_PixelFormat* format) {
    Color::mFormat = format;
}


Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SetRGBA(r,g,b,a);
}


void Color::SetRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    mColor = SDL_MapRGBA(mFormat,r,g,b,a);
}

void Color::SetRed(uint8_t r) {
    uint8_t temp;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &temp, &g, &b , &a);
    SetRGBA(r,g,b,a);

}
void Color::SetGreen(uint8_t g) {
    uint8_t r;
    uint8_t temp;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &temp, &b , &a);
    SetRGBA(r,g,b,a);
}
void Color::SetBlue(uint8_t b) {
    uint8_t r;
    uint8_t g;
    uint8_t temp;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &temp , &a);
    SetRGBA(r,g,b,a);
}
void Color::SetAlpha(uint8_t a) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t temp;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b , &temp);
    SetRGBA(r,g,b,a);
}

uint8_t Color::GetRed() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b , &a);
    return r;
}
uint8_t Color::GetBlue() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b , &a);
    return b;
}
uint8_t Color::GetGreen() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b , &a);
    return g;
}
uint8_t Color::GetAplha() const {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b , &a);
    return a;
}

Color Color::Evaluate1MinusSourceAlpha(const Color& source, const Color& destination) {
    uint8_t alpha = source.GetAplha();
    float sourceAlpha = float(alpha) / 255.0f;
    double destAlpha = 1.0f - sourceAlpha;

    Color outColor;

    outColor.SetAlpha(255);
    outColor.SetRed(float(source.GetRed()) * sourceAlpha + float(destination.GetRed()) * destAlpha);
    outColor.SetGreen(float(source.GetGreen()) * sourceAlpha + float(destination.GetGreen()) * destAlpha);
    outColor.SetBlue(float(source.GetBlue()) * sourceAlpha + float(destination.GetBlue()) * destAlpha);

    return outColor;
}
