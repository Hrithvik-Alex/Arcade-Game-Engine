//
// Created by Hrithvik  Alex on 2020-04-09.
//


#include "GameScene.h"

GameScene::GameScene(std::unique_ptr<Game> gamePtr): mGame(std::move(gamePtr)){}

void GameScene::init() {
    mGame->init(gameController);
}

void GameScene::update(uint32_t dt) {
    mGame->update(dt);
}

void GameScene::draw(Screen& screen) {
    mGame->draw(screen);
}

const std::string& GameScene::getSceneName() const {

    return mGame->getName();
}