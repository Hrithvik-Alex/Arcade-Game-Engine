//
// Created by Hrithvik  Alex on 2020-04-19.
//

#include "Tetromino.h"
#include "../../graphics/color.h"
#include "../../graphics/Screen.h"
#include "../../App/App.h"
#include "../BreakOut/Boundary.h"
#include "../../Utils/utils.h"
#include <stdlib.h>

Tetromino::Tetromino(): Tetromino(static_cast<TetrominoType>(rand() % 7), 1000) {}
Tetromino::Tetromino(float velocity): Tetromino(static_cast<TetrominoType>(rand() % 7), velocity) {}
Tetromino::Tetromino(TetrominoType tetrominoType, float velocity): mTetrominoType(tetrominoType), mVelocity(velocity) {}

void Tetromino::init(const Vec2D& startPos) {
   mRotationIndex = 0;
   currentDT = 0;
   currentTop = startPos;
   isStopped = false;
   Color fillColor;
   switch(mTetrominoType) {
        case I: {
            fillColor = Color::Cyan();
            break;
        };
        case J: {
            fillColor = Color::Blue();
            break;
        };
        case L: {
            fillColor = Color::Orange();
            break;
        };
        case O: {
            fillColor = Color::Yellow();
            break;
        };
        case S: {
            fillColor = Color::Green();
            break;
        };
        case T: {
            fillColor = Color::Magenta();
            break;
        };
        case Z: {
            fillColor = Color::Red();
            break;
        };
   }
   mFillColor = fillColor;
   renderTetrominoRotations(true);
}
void Tetromino::update(uint32_t dt) {
    if(!isStopped) {
        currentDT+=dt;
        if(currentDT >= mVelocity) {
            currentDT -= mVelocity;
            movePosition(Vec2D(0,BLOCK_HEIGHT));
        }
    }
}


void Tetromino::draw(Screen& screen) {

    for(auto rectangle : getCurrentRotation().rects) {
        screen.Draw(rectangle, Color::Black(), true, mFillColor);
    }
}

void Tetromino::movePosition(const Vec2D& pos) {
    if(!isStopped) {
        std::vector<BoundaryEdge> edges;
        currentTop += pos;
        if(hasCollidedWithEdge(edges)) {
            for(auto edge : edges) {
                fixCollidedEdge(edge);
                if(edge.normal == UP_DIR) {
                    isStopped = true;
                }
            }
        }
        renderTetrominoRotations();
    }
}


bool Tetromino::hasCollided(const Vec2D &pos) {
    for(auto rect : getCurrentRotation().rects) {
        if(rect.contains(pos)) return true;
    }
    return false;

}

void Tetromino::rotateLeft() {
    mRotationIndex = (mRotationIndex + mRectangleRotations.size() - 1) % mRectangleRotations.size();
    renderTetrominoRotations(false, true);
}

void Tetromino::rotateRight() {
    mRotationIndex = (mRotationIndex + 1) % mRectangleRotations.size();
    renderTetrominoRotations(false, true);

}


bool Tetromino::hasCollidedWithEdge(std::vector<BoundaryEdge>& edges) {
    float minX = currentTop.GetX() - getCurrentRotation().width*BLOCK_WIDTH;
    float maxX = currentTop.GetX() + getCurrentRotation().width*BLOCK_WIDTH;
    float maxY = currentTop.GetY() + getCurrentRotation().height*BLOCK_HEIGHT;

    bool isCollided = false;

    if(minX < 0) {
        BoundaryEdge edge;
        edge.edge = {Vec2D(0,0), Vec2D(0,App::Singleton().height())};
        edge.normal = RIGHT_DIR;
        edges.push_back(edge);
        isCollided = true;
    }
    if(maxX > App::Singleton().width()) {
        BoundaryEdge edge;
        edge.edge = {Vec2D(App::Singleton().width(),0), Vec2D(App::Singleton().width(),App::Singleton().height())};
        edge.normal = LEFT_DIR;
        edges.push_back(edge);
        isCollided = true;

    }
    if(maxY > App::Singleton().height()) {
        BoundaryEdge edge;
        edge.edge = {Vec2D(0,App::Singleton().height()), Vec2D(App::Singleton().width(),App::Singleton().height())};
        edge.normal = UP_DIR;
        edges.push_back(edge);
        isCollided = true;
    }

    return isCollided;

}

void Tetromino::fixCollidedEdge(BoundaryEdge &edge) {
    float widthDisplaced = 0.0f;
    float heightDisplaced = 0.0f;

    if(edge.normal == RIGHT_DIR) {
        widthDisplaced = (currentTop.GetX() - getCurrentRotation().width*BLOCK_WIDTH);
    } else if (edge.normal == LEFT_DIR) {
        widthDisplaced = (currentTop.GetX() + getCurrentRotation().width*BLOCK_WIDTH - App::Singleton().width());
    } else if (edge.normal == UP_DIR) {
        heightDisplaced = (currentTop.GetY() + getCurrentRotation().height*BLOCK_HEIGHT - App::Singleton().height());
    }
    currentTop += Vec2D(-widthDisplaced, -heightDisplaced);
}

void Tetromino::renderTetrominoRotations(bool initial, bool rotate) {

    std::vector<TetroPosition> rectRotations;
    Vec2D startPos = currentTop;
    std::vector<Rectangle> rects;
    float width;
    float height;
    switch(mTetrominoType) {
        case I: {

            // horizontal
            width = 2.0f;
            height = 1.0f;
            if(rotate) startPos -= {BLOCK_WIDTH*0.5f,-1.0f*BLOCK_HEIGHT};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }
            rectRotations.push_back({rects, startPos, width, height});

            // vertical
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos += {BLOCK_WIDTH*0.5f,-1.0f*BLOCK_HEIGHT};
            width = 0.5f;
            height = 4.0f;
            float blockX = startPos.GetX() - width*BLOCK_WIDTH;
            float startY = startPos.GetY();
            curRect = Rectangle(Vec2D(blockX, startY),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }
            rectRotations.push_back({rects, startPos, width, height});

            break;
        };
        case J: {
            // first

            width = 1.5f;
            height = 2.0f;
            if(initial) startPos += {BLOCK_WIDTH/2.0f,0};
            if(rotate) startPos += {BLOCK_WIDTH*0.5f,0};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }
            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            // second
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos += {BLOCK_WIDTH*0.5f,0};
            width = 1.0f;
            height = 3.0f;
            startX = startPos.GetX();
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }
            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});


            // third
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos -= {BLOCK_WIDTH*0.5f,0};
            width = 1.5f;
            height = 2.0f;
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY() + BLOCK_HEIGHT),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }
            curRect.MoveBy(Vec2D(-static_cast<float>(3*BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});


            // fourth
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos -= {BLOCK_WIDTH*0.5f,0};
            width = 1.0f;
            height = 3.0f;
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }
            curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),-static_cast<float>(3*BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            break;
        };
        case L: {
            // first

            width = 1.5f;
            height = 2.0f;
            if(initial) startPos += {BLOCK_WIDTH/2.0f,0};
            if(rotate) startPos += {BLOCK_WIDTH*0.5f,0};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);
            curRect.MoveBy(Vec2D(0,-static_cast<float>(BLOCK_HEIGHT)));
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            rectRotations.push_back({rects, startPos, width, height});


            // second
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos += {BLOCK_WIDTH*0.5f,0};
            width = 1.0f;
            height = 3.0f;
            startX = startPos.GetX();
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }
            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),-static_cast<float>(3*BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});


            // third
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos -= {BLOCK_WIDTH*0.5f,0};
            width = 1.5f;
            height = 2.0f;
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            curRect.MoveBy(Vec2D(static_cast<float>(2*BLOCK_WIDTH),0));
            rects.push_back(curRect);
            curRect.MoveBy(Vec2D(-static_cast<float>(2*BLOCK_WIDTH),static_cast<float>(BLOCK_HEIGHT)));
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            rectRotations.push_back({rects, startPos, width, height});


            // fourth
            rects.clear();
            startPos = currentTop;
            if(rotate) startPos -= {BLOCK_WIDTH*0.5f,0};
            width = 1.0f;
            height = 3.0f;
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);
            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }
            curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            break;
        };
        case O: {
            width = 1.0f;
            height = 2.0f;
            float startX = startPos.GetX() - BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                for(size_t i = 0; i < NUM_SIDES/2; i++) {
                    rects.push_back(curRect);
                    curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
                }
                curRect.MoveTo(Vec2D(startX,curRect.getTopLeftPoint().GetY() + BLOCK_HEIGHT));
            }

            rectRotations.push_back({rects, startPos, width, height});

            break;
        };
        case S: {

            // first
            width = 1.5f;
            height = 2.0f;
            if(initial) startPos += {BLOCK_WIDTH/2.0f,0};
            if(rotate) startPos -= {BLOCK_WIDTH/2.0f,0};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY() + BLOCK_HEIGHT),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            rectRotations.push_back({rects, startPos, width, height});

            // second
            rects.clear();
            startPos = currentTop;
            width = 1.0f;
            height = 3.0f;
            if(rotate) startPos += {BLOCK_WIDTH/2.0f,0};
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            rectRotations.push_back({rects, startPos, width, height});


            break;
        };
        case T: {
            // first

            width = 1.5f;
            height = 2.0f;
            if(initial) startPos += {BLOCK_WIDTH/2.0f,0};
            if (rotate) startPos += {BLOCK_WIDTH/2.0f,0};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(2*BLOCK_WIDTH),static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            // second
            rects.clear();
            startPos = currentTop;
            width = 1.0f;
            height = 3.0f;
            if (rotate) startPos += {BLOCK_WIDTH/2.0f,0};
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),-static_cast<float>(2*BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            // third
            rects.clear();
            startPos = currentTop;
            width = 1.5f;
            height = 2.0f;
            if (rotate) startPos -= {BLOCK_WIDTH/2.0f,0};
            startX = startPos.GetX() - width*BLOCK_WIDTH;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()+BLOCK_HEIGHT),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(2*BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            // fourth
            rects.clear();
            startPos = currentTop;
            width = 1.0f;
            height = 3.0f;
            if (rotate) startPos -= {BLOCK_WIDTH/2.0f,0};
            startX = startPos.GetX() ;
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES-1; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),-static_cast<float>(2*BLOCK_HEIGHT)));
            rects.push_back(curRect);

            rectRotations.push_back({rects, startPos, width, height});

            break;
        };
        case Z: {
            // first

            width = 1.5f;
            height = 2.0f;
            if(initial) startPos += {BLOCK_WIDTH/2.0f,0};
            if(rotate) startPos += {BLOCK_WIDTH/2.0f,0};
            float startX = startPos.GetX() - width*BLOCK_WIDTH;
            Rectangle curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),static_cast<float>(BLOCK_HEIGHT)));

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(static_cast<float>(BLOCK_WIDTH),0));
            }

            rectRotations.push_back({rects, startPos, width, height});


            // second
            rects.clear();
            startPos = currentTop;
            width = 1.0f;
            height = 3.0f;
            if(rotate) startPos -= {BLOCK_WIDTH/2.0f,0};
            startX = startPos.GetX();
            curRect = Rectangle(Vec2D(startX, startPos.GetY()),BLOCK_WIDTH,BLOCK_HEIGHT);

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            curRect.MoveBy(Vec2D(-static_cast<float>(BLOCK_WIDTH),-static_cast<float>(BLOCK_HEIGHT)));

            for(size_t i = 0; i < NUM_SIDES/2; i++) {
                rects.push_back(curRect);
                curRect.MoveBy(Vec2D(0,static_cast<float>(BLOCK_HEIGHT)));
            }

            rectRotations.push_back({rects, startPos, width, height});



            break;
        };
    }
    currentTop = rectRotations[mRotationIndex].top;
    mRectangleRotations = rectRotations;
}

