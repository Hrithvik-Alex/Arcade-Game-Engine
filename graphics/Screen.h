//
// Created by Hrithvik  Alex on 2019-12-27.
//

#ifndef LINES_SCREEN_H
#define LINES_SCREEN_H

#include <stdint.h>
#include <vector>
#include <functional>
#include "ScreenBuffer.h"
#include "color.h"
#include "../Utils/vec2D.h"


class Vec2D;
class Line2D;
class Triangle;
class Rectangle;
class Circle;
struct SDL_Window;
struct SDL_Surface;
class BMPImage;
class SpriteSheet;
struct Sprite;
class BitmapFont;

struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;

class Screen {
public:
    Screen();
    ~Screen();

    SDL_Window* Init(uint32_t width, uint32_t height, uint32_t mag, bool fast = true);
    void SwapScreen();

    inline void SetClearColor(const Color& col) {clear = col;}
    inline uint32_t Width() const {return mWidth;}
    inline uint32_t Height() const {return mHeight;}

    void Draw(int x, int y, const Color& color);
    void Draw(const Vec2D& vec, const Color& color);
    void Draw(const Line2D& line, const Color& color);
    void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const Rectangle& rectangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor = Color::White(), bool rotate = false, float rotateAngle = 0, Vec2D centerPoint = Vec2D::Zero);
    void Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor = Color::White(), bool rotate = false, float rotateAngle = 0, Vec2D centerPoint = Vec2D::Zero);
    void Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor = Color::White());

private:

    // putting it in private restricts actual use
    Screen(const Screen& otherScreen);
    Screen& operator=(const Screen& otherScreen);

    void clearScreen();

    using FillPolyFunc = std::function<Color (uint32_t x, uint32_t y)>;

    void fillPoly(const std::vector<Vec2D>& points, FillPolyFunc func, bool rotate = false, float rotateAngle = 0, Vec2D centerPoint = Vec2D::Zero);

    uint32_t mWidth;
    uint32_t mHeight;

    Color clear;
    ScreenBuffer backBuf;

    SDL_Window* win;
    SDL_Surface* surface;

    SDL_Renderer* mRenderer;
    SDL_PixelFormat* mPixelFormat;
    SDL_Texture* mTexture;
    bool mFast;
};


#endif //LINES_SCREEN_H
