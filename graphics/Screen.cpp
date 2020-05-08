//
// Created by Hrithvik  Alex on 2019-12-27.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "Screen.h"
#include "../Utils/vec2D.h"
#include "../shapes/Line2D.h"
#include "../shapes/Triangle.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "BMPImage.h"
#include "SpriteSheet.h"
#include "BitmapFont.h"
#include "../Utils/utils.h"
#include "SDL.h"

Screen::Screen(): mHeight(0), mWidth(0), win(nullptr), surface(nullptr), mRenderer(nullptr), mPixelFormat(nullptr), mTexture(nullptr) {}

Screen::~Screen() {

    if(mPixelFormat) {
        SDL_FreeFormat(mPixelFormat);
        mPixelFormat = nullptr;
    }

    if(mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    if(mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    if(win) {
        SDL_DestroyWindow(win);
        win = nullptr;
    }
    SDL_Quit();
}

SDL_Window* Screen::Init(uint32_t width, uint32_t height, uint32_t mag, bool fast) {


    mFast = fast;
//    initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "cant init video" << std::endl;
        return nullptr;
    }
// setting width/height variables
    mWidth = width;
    mHeight = height;
// creates window
    win = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * mag, height * mag, 0);

    if(win) {

        uint8_t rClear = 0;
        uint8_t gClear = 0;
        uint8_t bClear = 0;
        uint8_t aClear = 255;

        if(mFast) {
            mRenderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if(mRenderer == nullptr) {
                std::cout << "Renderer not created" << std::endl;
                return nullptr;
            }

            SDL_SetRenderDrawColor(mRenderer, rClear, bClear, gClear, aClear);

        } else {
            //        get reference to surface of window

            surface = SDL_GetWindowSurface(win);
        }

        mPixelFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(win));

        if(mFast) {
            mTexture = SDL_CreateTexture(mRenderer, mPixelFormat->format, SDL_TEXTUREACCESS_STREAMING, width, height);
        }
// initilaize color with current surface's pixel format
        Color::InitColorFormat(mPixelFormat);
// set clear color
        clear = Color(rClear, gClear, bClear, aClear);
// initialize back buffer
        backBuf.Init(mPixelFormat->format, mWidth, mHeight);
// clear back buffer
        backBuf.Clear(clear);
    }

    return win;
}

void Screen::SwapScreen() {

    if(win) {
        // clears front buffer
        clearScreen();

        uint8_t* textureData;

        if(mFast) {
            uint8_t* textureData = nullptr;
            int texturePitch = 0;

            if(SDL_LockTexture(mTexture, nullptr, (void**)&textureData, &texturePitch) >= 0) {
                SDL_Surface* surface = backBuf.GetSurface();
                memcpy(textureData, surface->pixels, surface->w*surface->h*mPixelFormat->BytesPerPixel);
                SDL_UnlockTexture(mTexture);
                SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
                SDL_RenderPresent(mRenderer);
            }
        } else {
            // moves content from back buffer onto the front surface buffer
            SDL_BlitScaled(backBuf.GetSurface(), nullptr, surface, nullptr);
// update window to show current surface buffer
            SDL_UpdateWindowSurface(win);
        }
// clear back buffer
        backBuf.Clear(clear);
    }
}

void Screen::clearScreen() {

    if(win) {
        if(mFast) {
            SDL_RenderClear(mRenderer);
        } else {
            SDL_FillRect(surface, nullptr, clear.GetPixelColor());
        }
    }
}

void Screen::fillPoly(const std::vector<Vec2D>& points, FillPolyFunc func, bool rotate, float rotateAngle, Vec2D centerPoint) {
    if(points.size() > 0) {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();

        for (size_t i = 1; i < points.size(); ++i) {
            if(points[i].GetY() < top) {
                top = points[i].GetY();
            }
            if(points[i].GetY() > bottom) {
                bottom = points[i].GetY();
            }
            if(points[i].GetX() < left) {
                left = points[i].GetX();
            }
            if(points[i].GetX() > right) {
                right = points[i].GetX();
            }
        }

        for(int pixelY = top; pixelY < bottom; ++pixelY) {
            std::vector<float> nodeXVec;

            size_t j = points.size() - 1;

            for(size_t i = 0; i < points.size(); ++i) {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();

                if((IsLessThanOrEqual(pointiY, (float)pixelY) && pointjY > (float)pixelY) || (IsLessThanOrEqual(pointjY, (float)pixelY) && pointiY > (float)pixelY)) {
                    float denom = pointjY - pointiY;
                    if(IsEqual(denom, 0)) {
                        continue;
                    }

                    float ix = points[i].GetX();
                    float jx = points[j].GetX();

                    float x = points[i].GetX() + (pixelY - pointiY)/(denom) * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }
                j = i;
            }

            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

            for (size_t k = 0; k < nodeXVec.size(); k+=2) {
                if(nodeXVec[k] > right) {
                    break;
                }
                if(nodeXVec[k+1] > left) {
                    if (nodeXVec[k] < left) {
                        nodeXVec[k] = left;
                    }
                    if(nodeXVec[k+1] > right) {
                        nodeXVec[k+1] = right;
                    }

                    for(int pixelX = round(nodeXVec[k]); pixelX < round(nodeXVec[k+1]); ++pixelX) {
                        if(rotate) {
                            Vec2D currentPoint = {static_cast<float>(pixelX), static_cast<float>(pixelY)};
                            Vec2D rotatedPoint = currentPoint.RotateResult(rotateAngle, centerPoint);
                            Draw(rotatedPoint, func(pixelX, pixelY));

                        } else {
                            Draw(pixelX, pixelY, func(pixelX, pixelY));
                        }
                    }
                }
            }
        }

    }



}


void Screen::Draw(int x, int y, const Color& color) {
    if(win) {
        backBuf.SetPixel(color, x, y);
    }
}
void Screen::Draw(const Vec2D& vec, const Color& color) {
    if(win) {
        backBuf.SetPixel(color, round(vec.GetX()), round(vec.GetY()));
    }
}

void Screen::Draw(const Line2D& line, const Color& color) {
    if(win) {
        int dx,dy;
        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        signed const char ix((dx > 0) - (dx < 0));
        signed const char iy((dy > 0) - (dy < 0));

        dx = abs(dx) * 2;
        dy = abs(dy) * 2;

        //Bresenham's Line Algorithm
        Draw(x0, y0, color);

        if(dx>=dy) {
            //move in the x
            int d = dy-dx/2;
            while(x0 != x1) {
                if(d >= 0) {
                    d -= dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;
                Draw(x0,y0,color);
            }
        }
        else {
            // move in the y
            int d = dx-dy/2;
            while(y0 != y1) {
                if(d >= 0) {
                    d -= dy;
                    x0 += ix;
                }
                d += dx;
                y0 += iy;
                Draw(x0,y0,color);
            }
        }

    }
}

void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor) {
    if(fill) {
        fillPoly(triangle.getPoints(), [fillColor](uint32_t x, uint32_t y){ return fillColor;});
    }


    Line2D p0p1 = Line2D(triangle.getP0(), triangle.getP1());
    Line2D p1p2 = Line2D(triangle.getP1(), triangle.getP2());
    Line2D p2p0 = Line2D(triangle.getP2(), triangle.getP0());

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p0, color);

}

void Screen::Draw(const Rectangle& rectangle, const Color& color, bool fill, const Color& fillColor) {
    if(fill) {
        fillPoly(rectangle.getPoints(), [fillColor](uint32_t x, uint32_t y){ return fillColor;});
    }

    std::vector<Vec2D> points = rectangle.getPoints();

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p1p2 = Line2D(points[1], points[2]);
    Line2D p2p3 = Line2D(points[2], points[3]);
    Line2D p3p0 = Line2D(points[3], points[0]);

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p3, color);
    Draw(p3p0, color);

}

void Screen::Draw(const Circle& circle, const Color& color,  bool fill, const Color& fillColor) {


    static unsigned int SEGMENTS = 30;

    std::vector<Vec2D> points;
    std::vector<Line2D> lines;


    float angle = (2.0f * PI) / float(SEGMENTS);

    Vec2D p0 = Vec2D(circle.getCenter().GetX() + circle.getRadius(), circle.getCenter().GetY());
    Vec2D p1 = p0;
    Line2D curLine;


    for (unsigned int i = 0; i < SEGMENTS; ++i) {
        p1.Rotate(angle, circle.getCenter());
        curLine.SetP1(p1);
        curLine.SetP0(p0);
        lines.push_back(curLine);
        p0 = p1;
        points.push_back(p0);
    }

    if(fill) {
        fillPoly(points, [fillColor](uint32_t x, uint32_t y){ return fillColor;});
    }

    for(const Line2D& line : lines) {
        Draw(line, color);
    }

}

void Screen::Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& pos, const Color& overlayColor, bool rotate, float rotateAngle, Vec2D centerPoint) {

    float rVal = static_cast<float>(overlayColor.GetRed()) / 255.0f;
    float gVal = static_cast<float>(overlayColor.GetGreen()) / 255.0f;
    float bVal = static_cast<float>(overlayColor.GetBlue()) / 255.0f;
    float aVal = static_cast<float>(overlayColor.GetAplha()) / 255.0f;

    uint32_t width = sprite.width;
    uint32_t height = sprite.height;

    const std::vector<Color>& pixels = image.getPixels();

    auto topLeft = pos;
    auto topRight = pos + Vec2D(width, 0);
    auto bottomLeft = pos + Vec2D(0, height);
    auto bottomRight = pos + Vec2D(width, height);

    std::vector<Vec2D> points = {topLeft, bottomLeft, bottomRight, topRight};

    Vec2D xAxis = topRight - topLeft;
    Vec2D yAxis = bottomLeft - topLeft;

    const float invXAxisLengthSq = 1.0f / xAxis.Mag2();
    const float invYAxisLengthSq = 1.0f / yAxis.Mag2();
    fillPoly(points, [&](uint32_t px, uint32_t py){
        Vec2D p = {static_cast<float>(px), static_cast<float>(py)};
        Vec2D d = p - topLeft;

        float u = invXAxisLengthSq * d.Dot(xAxis);
        float v = invYAxisLengthSq * d.Dot(yAxis);

        u = Clamp(u, 0.0f, 1.0f);
        v = Clamp(v, 0.0f, 1.0f);

        float tx = roundf(u * static_cast<float>(sprite.width));
        float ty = roundf(v * static_cast<float>(sprite.height));

        Color imageColor = pixels[GetIndex(image.getWidth(),ty+sprite.yPos,tx + sprite.xPos)];
        Color newColor = {static_cast<uint8_t>(imageColor.GetRed() * rVal), static_cast<uint8_t>(imageColor.GetGreen() * gVal), static_cast<uint8_t>(imageColor.GetBlue() * bVal), static_cast<uint8_t>(imageColor.GetAplha() * aVal)};

        return newColor;


    }, rotate, rotateAngle, centerPoint);

}

void Screen::Draw(const SpriteSheet& ss, const std::string& spriteName, const Vec2D& pos, const Color& overlayColor, bool rotate, float rotateAngle, Vec2D centerPoint) {
    Draw(ss.getBMPImage(), ss.getSprite(spriteName),pos,overlayColor,rotate,rotateAngle,centerPoint);
}

void Screen::Draw(const BitmapFont& font, const std::string& textLine, const Vec2D& pos, const Color& overlayColor) {
    uint32_t xPos = pos.GetX();
    uint32_t yPos = pos.GetY();

    const SpriteSheet& ss = font.getSpriteSheet();

    for(char c : textLine) {
        if(c == ' ') {
            xPos += font.getFontSpacingBetweenWords();
            continue;
        }

        Sprite sprite = ss.getSprite(std::string("") + c);

        Draw(ss.getBMPImage(), sprite, Vec2D(xPos,yPos), overlayColor);

        xPos += sprite.width + font.getFontSpacingBetweenLetters();
    }

}


