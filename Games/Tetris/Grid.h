//
// Created by Hrithvik  Alex on 2020-04-25.
//

#ifndef LINES_GRID_H
#define LINES_GRID_H

#include <stdint.h>
#include <vector>
#include "Tetromino.h"
#include "../../graphics/color.h"

class Screen;
class Vec2D;
class Rectangle;
class Tetromino;

struct FillPoint {
    int x;
    int y;
};

struct FillRectangle {
    Rectangle rect;
    Color fillColor;
};

class Grid {
public:

    static const int GRID_WIDTH = 10;
    static const int GRID_HEIGHT = 20;

    Grid();
    Grid(Tetromino* tetromino);

    void init();
    void update(uint32_t dt);
    void draw(Screen& screen);

    Tetromino* addToGrid(float velocity);
    bool didCollide();
    Tetromino* spawnNewTetromino(float velocity);
    void dropTetromino();



private:
    Tetromino* mCurrentTetromino;
    std::vector<FillRectangle> mRectangles;
    std::vector<FillRectangle> mCurrentDrop;
    std::vector<std::vector<bool>> mFilledGrid;

    std::vector<FillPoint> getCurrentFill();
    void lineFilledUpdate();
    int calculateCurrentDrop();

    int mScore;
};


#endif //LINES_GRID_H
