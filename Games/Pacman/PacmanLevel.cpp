//
// Created by Hrithvik  Alex on 2020-05-08.
//


#include "PacmanLevel.h"
#include "../../Utils/FileCommandLoader.h"
#include "../../graphics/Screen.h"

bool PacmanLevel::init(const std::string& levelPath) {
    return loadLevel(levelPath);
}

void PacmanLevel::update(uint32_t dt) {

}

void PacmanLevel::draw(Screen& screen) {

    // wall debug
    for(const auto& wall: mWalls) {
        screen.Draw(wall.getRectangle(), Color::Blue());
    }
}

bool PacmanLevel::loadLevel(const std::string& levelPath) {

    FileCommandLoader fileCommandLoader;

    Command tileWidthCommand;
    tileWidthCommand.command = "tile_width";
    tileWidthCommand.parseFunc = [this](ParseFuncParams params) {
        mTiles.back().width = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(tileWidthCommand);

    Command tileHeightCommand;
    tileHeightCommand.command = "tile_height";
    tileHeightCommand.parseFunc = [this](ParseFuncParams params) {
        mTileHeight = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(tileHeightCommand);

    Command tileCommand;
    tileCommand.command = "tile";
    tileCommand.parseFunc = [this](ParseFuncParams params) {
        mTiles.emplace_back(Tile());
    };

    fileCommandLoader.addCommand(tileCommand);

    Command tileSymbolCommand;
    tileSymbolCommand.command = "tile_symbol";
    tileSymbolCommand.parseFunc = [this](ParseFuncParams params) {
        mTiles.back().symbol = FileCommandLoader::readChar(params);
    };

    fileCommandLoader.addCommand(tileSymbolCommand);

    Command tileCollisionCommand;
    tileCollisionCommand.command = "tile_collision";
    tileCollisionCommand.parseFunc = [this](ParseFuncParams params) {
        mTiles.back().collidable = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(tileCollisionCommand);

    Vec2D layoutOffset;

    Command layoutOffsetCommand;
    layoutOffsetCommand.command = "layout_offset";
    layoutOffsetCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params) {
        mLayoutOffset = FileCommandLoader::readSize(params);
        layoutOffset = mLayoutOffset;
    };

    fileCommandLoader.addCommand(layoutOffsetCommand);

    Command layoutCommand;
    layoutCommand.command = "layout";
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params) {
        int startingX = layoutOffset.GetX();

        for(int c = 0; c < params.line.length(); ++c) {
            Tile* tile = getTileForSymvbol(params.line[c]);

            if(tile) {
                tile->position = Vec2D(startingX, layoutOffset.GetY());
            }

            if(tile->collidable > 0) {
                Excluder wall;
                wall.init(Rectangle(Vec2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(mTileHeight)));

                mWalls.push_back(wall);
            }

            startingX += tile->width;
        }

        layoutOffset += Vec2D(0, mTileHeight);
    };

    fileCommandLoader.addCommand(layoutCommand);


    return fileCommandLoader.loadFile(levelPath);
}

PacmanLevel::Tile* PacmanLevel::getTileForSymvbol(char symbol) {
    for(size_t i = 0; i < mTiles.size(); ++i) {
        if(mTiles[i].symbol == symbol) {
            return &mTiles[i];
        }
    }
    return nullptr;
}