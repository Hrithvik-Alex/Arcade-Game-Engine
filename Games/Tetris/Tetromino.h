//
// Created by Hrithvik  Alex on 2020-04-19.
//

#ifndef LINES_TETROMINO_H
#define LINES_TETROMINO_H

#include "../../shapes/Rectangle.h"
#include "../../graphics/color.h"
#include <stdint.h>
#include <vector>

enum TetrominoType {
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z,
};

struct TetroPosition {
    std::vector<Rectangle> rects;
    Vec2D top;
    float width;
    float height;
};


class Screen;
class Vec2D;
class Line2D;
class BoundaryEdge;
class Grid;

class Tetromino {
public:

    static const uint32_t BLOCK_WIDTH = 13;
    static const uint32_t BLOCK_HEIGHT = 13;

    Tetromino();
    Tetromino(float velocity);
    Tetromino(TetrominoType tetrominoType, float velocity);

    void init(const Vec2D& startPos);
    void update(uint32_t dt);
    void draw(Screen& screen);

    void rotateLeft();
    void rotateRight();

    void movePosition(const Vec2D& pos);
    bool hasCollided(const Vec2D& pos);
    bool hasCollidedWithEdge(std::vector<BoundaryEdge>& edges);
    void fixCollidedEdge(BoundaryEdge& edge);

    inline bool isTetrominoStopped() {return isStopped;}
    inline void stopTetromino() {isStopped = true;}
    inline TetroPosition getCurrentRotation() {return mRectangleRotations[mRotationIndex];}

    inline Color getFillColor() {return mFillColor;}

private:
    static const int NUM_SIDES = 4;
    int currentDT;
    Vec2D currentTop;
    bool isStopped;

    void renderTetrominoRotations(bool initial = false, bool rotate = false);
    TetrominoType mTetrominoType;
    std::vector<TetroPosition> mRectangleRotations;
    int mRotationIndex;
    Color mFillColor;
    float mVelocity;


};


#endif //LINES_TETROMINO_H
