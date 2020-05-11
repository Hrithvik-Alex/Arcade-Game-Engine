//
// Created by Hrithvik  Alex on 2020-05-08.
//

#ifndef LINES_PACMANLEVEL_H
#define LINES_PACMANLEVEL_H

#include "../../Utils/vec2D.h"
#include "../BreakOut/Excluder.h"
#include "PacmanGameUtils.h"
#include "../../graphics/SpriteSheet.h"
#include <string>
#include <vector>
#include <random>

class Screen;
class Pacman;
class Ghost;

class PacmanLevel {
public:

    bool init(const std::string& levelPath, const SpriteSheet* noptrSpriteSheet);
    void update(uint32_t dt, Pacman& pacman, std::vector<Ghost>& ghosts);
    void draw(Screen& screen);

    bool willCollide(const Rectangle& bbox, PacmanMovement direction) const;

    inline Vec2D getLayoutOffset() const {return mLayoutOffset;}
    inline Vec2D getPacmanSpawnLocation() const {return mPacmanSpawnLocation;}

    bool isLevelOver() const;
    void increaseLevel();
    void resetToFirstLevel();
    void resetLevel();

    inline const std::vector<Vec2D>& getGhostSpawnPoints() {return mGhostSpawnPoints;}

private:
    struct Tile {
        Vec2D position = Vec2D::Zero;
        Vec2D offset = Vec2D::Zero;
        int width = 0;
        int collidable = 0;
        int isTeleportTile = 0;
        int excludePelletTile = 0;
        int pacmanSpawnPoint = 0;
        int blinkySpawnPoint = 0;
        int inkySpawnPoint = 0;
        int pinkySpawnPoint = 0;
        int clydeSpawnPoint = 0;
        int itemSpawnPoint = 0;
        char teleportToSymbol = 0;
        char symbol = '-';

    };

    struct Pellet {
        uint32_t score = 0;
        Rectangle mBBox;
        int powerPellet = 0;
        int eaten = 0;
    };

    struct BonusItem {
        uint32_t score = 0;
        Rectangle bbox;
        int eaten = 0;
        int spawned = 0;
        int spawnTime = -1;
    };

    struct BonusItemLevelProperties {
        uint32_t score = 0;
        std::string spriteName = "";
        uint32_t begin = 0; // which levels do they spawn at
        uint32_t end = 0;
    };

    bool loadLevel(const std::string& levelPath);
    Tile* getTileForSymvbol(char symbol);
    void resetPellets();
    bool hasEatenAllPellets() const;
    size_t numPelletsEaten() const;

    void getBonusItemSpriteName(std::string& spriteName, uint32_t& score) const;
    void spawnBonusItem();
    bool shouldSpawnBonusItem() const;

    std::vector<Vec2D> mGhostSpawnPoints;
    std::default_random_engine mGenerator;
    BonusItem mBonusItem;
    std::string mBonusItemSpriteName;
    const SpriteSheet* mnoptrSpriteSheet;
    std::vector<BonusItemLevelProperties> mBonusItemProperties;

    std::vector<Excluder> mWalls;
    std::vector<Tile> mTiles;

    std::vector<Tile> mExclusionTiles;
    std::vector<Pellet> mPelllets;

    Vec2D mPacmanSpawnLocation;
    Vec2D mLayoutOffset;
    size_t mTileHeight;
    int mCurrentLevel;


};


#endif //LINES_PACMANLEVEL_H
