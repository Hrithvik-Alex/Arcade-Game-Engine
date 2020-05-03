//
// Created by Hrithvik  Alex on 2020-04-27.
//

#include "SpriteSheet.h"
#include "../Utils/FileCommandLoader.h"
#include "../Utils/utils.h"
#include "../App/App.h"
#include <iostream>

SpriteSheet::SpriteSheet() {

}

bool SpriteSheet::load(const std::string& name) {
    bool loadedImage = mBMPImage.load(App::Singleton().getBasePath() + std::string("../Assets/" + name + ".bmp"));
    bool loadedSpriteSections = loadSpriteSections(App::Singleton().getBasePath() + std::string("../Assets/" + name + ".txt"));

    return loadedImage && loadedSpriteSections;
}

Sprite SpriteSheet::getSprite(const std::string& spriteName) const {

    for(int i = 0; i < mSections.size(); ++i) {
        if(stringCompare(mSections[i].key, spriteName)) {
            return mSections[i].sprite;
        }
    }
    return Sprite();
}

std::vector<std::string> SpriteSheet::spriteNames() const {
    std::vector<std::string> spriteNames;

    for(const auto& section : mSections) {
        spriteNames.push_back(section.key);
    }
    return spriteNames;
}

bool SpriteSheet::loadSpriteSections(const std::string& path) {
    FileCommandLoader fileCommandLoader;

    Command spriteCommand;
    spriteCommand.command = "sprite";

    spriteCommand.parseFunc = [&](ParseFuncParams params) {
        BMPImageSection section;
        mSections.push_back(section);
    };

    fileCommandLoader.addCommand(spriteCommand);

    Command keyCommand;
    keyCommand.command = "key";

    keyCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().key = FileCommandLoader::readString(params);
    };

    fileCommandLoader.addCommand(keyCommand);

    Command xPosCommand;
    xPosCommand.command = "xPos";

    xPosCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.xPos = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(xPosCommand);

    Command yPosCommand;
    yPosCommand.command = "yPos";

    yPosCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.yPos = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(yPosCommand);

    Command widthCommand;
    widthCommand.command = "width";

    widthCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.width = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";

    heightCommand.parseFunc = [&](ParseFuncParams params) {
        mSections.back().sprite.height = FileCommandLoader::readInt(params);
    };

    fileCommandLoader.addCommand(heightCommand);

    return fileCommandLoader.loadFile(path);
}
