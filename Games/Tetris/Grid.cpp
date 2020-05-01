//
// Created by Hrithvik  Alex on 2020-04-25.
//

#include "Grid.h"
#include "../../App/App.h"
#include "../../Input/GameController.h"
#include <cmath>


Grid::Grid() {}

Grid::Grid(Tetromino* tetromino): mCurrentTetromino(tetromino) {}

void Grid::init() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        mFilledGrid.push_back(std::vector<bool>(GRID_WIDTH, false));
    }
    mScore = 0;
}

void Grid::update(uint32_t dt) {
    calculateCurrentDrop();
}

void Grid::draw(Screen& screen) {
    for(FillRectangle fillGhost: mCurrentDrop) {
        screen.Draw(fillGhost.rect, Color::Black(), true, fillGhost.fillColor);
    }

    for(FillRectangle fillRect : mRectangles) {
        screen.Draw(fillRect.rect, Color::Black(), true, fillRect.fillColor);
    }
}

Tetromino* Grid::addToGrid(float velocity) {
    std::vector<FillPoint> fillPoints = getCurrentFill();

    for(FillPoint gridPoint : fillPoints) {
        mFilledGrid[gridPoint.y][gridPoint.x] = true;
    }

    for(Rectangle rect : mCurrentTetromino->getCurrentRotation().rects) {
        mRectangles.push_back({rect, mCurrentTetromino->getFillColor()});
    }

    lineFilledUpdate();
    return spawnNewTetromino(velocity);
}

bool Grid::didCollide() {
    for(FillPoint gridPoint : getCurrentFill()) {
        if(gridPoint.y < Grid::GRID_HEIGHT-1 &&  mFilledGrid[gridPoint.y + 1][gridPoint.x]) {
            return true;
        }
    }
    return false;
}

Tetromino* Grid::spawnNewTetromino(float velocity) {
    Tetromino* tetromino = new Tetromino({L},velocity);
    Vec2D start = {App::Singleton().width()/2.0f, 0};
    tetromino->init(start);
    delete mCurrentTetromino;
    mCurrentTetromino = tetromino;
    return mCurrentTetromino;
}


void Grid::dropTetromino() {
    int count = calculateCurrentDrop();
    mCurrentTetromino->movePosition({0,count * static_cast<float>(Tetromino::BLOCK_HEIGHT)});
    mCurrentTetromino->stopTetromino();
}


std::vector<FillPoint> Grid::getCurrentFill() {
    std::vector<FillPoint> currentFill;
    for(Rectangle rect : mCurrentTetromino->getCurrentRotation().rects) {
        FillPoint fillPoint;
        fillPoint.x = static_cast<int>(floor(rect.getTopLeftPoint().GetX())) / Tetromino::BLOCK_WIDTH;
        fillPoint.y = static_cast<int>(floor(rect.getTopLeftPoint().GetY())) / Tetromino::BLOCK_HEIGHT;
        currentFill.push_back(fillPoint);

    }
    return currentFill;
}

void Grid::lineFilledUpdate() {
    int fillCount = 0;
    for(size_t i = 0; i < GRID_HEIGHT; ++i) {
        bool isFilled = true;
        for (size_t j = 0; j < GRID_WIDTH; ++j) {
            if(!mFilledGrid[i][j]) {
                isFilled = false;
                break;
            }
        }

        if(isFilled) {
            std::vector<bool> current(mFilledGrid[0]);
            for (size_t r = 1; r <= i; ++r) {
                std::vector<bool> temp = mFilledGrid[r];
                mFilledGrid[r] = current;
                current = temp;
            }
            mFilledGrid[0] = std::vector<bool>(GRID_WIDTH, false);

            auto rect = std::begin(mRectangles);
            while (rect != std::end(mRectangles)) {
                int yIndex = static_cast<int>(floor((*rect).rect.getTopLeftPoint().GetY())) / Tetromino::BLOCK_HEIGHT;
                if (yIndex < i) {
                    (*rect).rect.MoveBy({0, static_cast<float>(Tetromino::BLOCK_HEIGHT)});
                    ++rect;
                } else if (yIndex == i) {
                    rect = mRectangles.erase(rect);
                } else {
                    ++rect;
                }
            }
            ++fillCount;
        }
    }
    if(fillCount==1) {
        mScore += 1000;
    } else if (fillCount > 1) {
        mScore += (fillCount - 1) * 2000 + 1000;
    }

    if(fillCount == 4) mScore += 1000;
}

int Grid::calculateCurrentDrop() {
    std::vector<FillPoint> currentFill = getCurrentFill();

    bool collisions = false;
    int count = 0;
    while(!collisions) {
        for(FillPoint gridPoint : currentFill) {
            if(gridPoint.y+1 == GRID_HEIGHT || mFilledGrid[gridPoint.y+1][gridPoint.x]) {
                collisions = true;
                break;
            }
        }

        if(!collisions) {
            for(FillPoint &gridPoint : currentFill) {
                gridPoint.y += 1;
            }


            ++count;
        }
    }

    Color transparentFill = mCurrentTetromino->getFillColor();
    transparentFill.SetAlpha(static_cast<uint8_t>(0.5 * 255));

    std::vector<FillRectangle> newFill;

    for(Rectangle rect : mCurrentTetromino->getCurrentRotation().rects) {
        rect.MoveBy({0, static_cast<float>(count)*Tetromino::BLOCK_HEIGHT});
        newFill.push_back({rect, transparentFill});
    }

    mCurrentDrop = newFill;

    return count;
}