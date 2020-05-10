//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANLEVEL_H
#define LINES_PACMANLEVEL_H

#include "../../Utils/vec2D.h"
#include "../BreakOut/Excluder.h"
#include "PacmanGameUtils.h"
#include <string>
#include <vector>

class Screen;
class Pacman;

class PacmanLevel {
public:

    bool init(const std::string& levelPath, Pacman* noptrPacman);
    void update(uint32_t dt);
    void draw(Screen& screen);

    bool willCollide(const Rectangle& bbox, PacmanMovement direction) const;

    inline Vec2D getLayoutOffset() const {return mLayoutOffset;}
    inline Vec2D getPacmanSpawnLocation() const {return mPacmanSpawnLocation;}

    bool isLevelOver() const;
    void increaseLevel();
    void resetToFirstLevel();

    void resetLevel();

private:
    struct Tile {
        Vec2D position = Vec2D::Zero;
        Vec2D offset = Vec2D::Zero;
        int width = 0;
        int collidable = 0;
        int isTeleportTile = 0;
        int excludePelletTile = 0;
        int pacmanSpawnPoint = 0;
        char teleportToSymbol = 0;
        char symbol = '-';

    };

    struct Pellet {
        uint32_t score = 0;
        Rectangle mBBox;
        int powerPellet = 0;
        int eaten = 0;
    };

    bool loadLevel(const std::string& levelPath);
    Tile* getTileForSymvbol(char symbol);
    void resetPellets();
    bool hasEatenAllPellets() const;

    size_t numPelletsEaten() const;

    std::vector<Excluder> mWalls;
    std::vector<Tile> mTiles;

    std::vector<Tile> mExclusionTiles;
    std::vector<Pellet> mPelllets;

    Vec2D mPacmanSpawnLocation;
    Vec2D mLayoutOffset;
    size_t mTileHeight;
    int mCurrentLevel;

    Pacman* mnoptrPacman;
};


#endif //LINES_PACMANLEVEL_H
