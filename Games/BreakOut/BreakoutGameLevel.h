//
// Created by Hrithvik  Alex on 2020-04-12.
//

#ifndef LINES_BREAKOUTGAMELEVEL_H
#define LINES_BREAKOUTGAMELEVEL_H

#include "Block.h"
#include <vector>
#include <stdint.h>

class Screen;
class Ball;
class Rectangle;

class BreakoutGameLevel {
public:
    BreakoutGameLevel();
    void init(const Rectangle& boundary);
    void load(const std::vector<Block>& blocks);
    void update(uint32_t dt, Ball& ball);
    void draw(Screen& screen);

    bool isLevelComplete() const;
    static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& filePath);

private:
    static const int BLOCK_WIDTH = 16;
    static const int BLOCK_HEIGHT = 8;
    void createDefaultLevel(const Rectangle& boundary);
    std::vector<Block> mBlocks;

};

#endif //LINES_BREAKOUTGAMELEVEL_H
