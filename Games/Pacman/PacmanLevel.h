//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANLEVEL_H
#define LINES_PACMANLEVEL_H

#include "../../Utils/vec2D.h"
#include "../BreakOut/Excluder.h"
#include <string>
#include <vector>

class Screen;

class PacmanLevel {
public:

    bool init(const std::string& levelPath);
    void update(uint32_t dt);
    void draw(Screen& screen);

private:
    struct Tile {
        Vec2D position = Vec2D::Zero;
        int width = 0;
        int collidable = 0;
        char symbol = '-';

    };

    bool loadLevel(const std::string& levelPath);
    Tile* getTileForSymvbol(char symbol);

    std::vector<Excluder> mWalls;
    std::vector<Tile> mTiles;

    Vec2D mLayoutOffset;
    size_t mTileHeight;
};


#endif //LINES_PACMANLEVEL_H
