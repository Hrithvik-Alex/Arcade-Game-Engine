//
// Created by Hrithvik  Alex on 2020-04-12.
//

#ifndef LINES_BLOCK_H
#define LINES_BLOCK_H

#include "Excluder.h"
#include "../../graphics/color.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block: public Excluder {
public:
    static const int UNBREAKABLE = -1;

    Block();
    void init(const Rectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
    void draw(Screen& screen);
    void bounce(Ball& ball, const BoundaryEdge& edge);

    void reduceHP();
    inline int getHP() const {return mHp;}
    inline bool isDestroyed() const {return mHp == 0;}
    inline const Color& getOutlineColor() const {return mOutlineColor;}
    inline const Color& getFillColor() const {return mFillColor;}
private:
    Color mOutlineColor;
    Color mFillColor;

    int mHp;
};


#endif //LINES_BLOCK_H
