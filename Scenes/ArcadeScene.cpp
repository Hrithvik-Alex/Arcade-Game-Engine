//
// Created by Hrithvik  Alex on 2020-04-07.
//

#include "ArcadeScene.h"
#include "../graphics/color.h"
#include "../graphics/Screen.h"
#include "../shapes/Rectangle.h"
#include "../Input/GameController.h"
#include <iostream>
#include "../App/App.h"
#include "GameScene.h"
#include "NotImplementedScene.h"
#include "../Games/BreakOut/BreakOut.h"
#include "../Games/Tetris/Tetris.h"
#include "../Games/Asteroids/Asteroids.h"
#include "Pacman/PacmanStartScene.h"

ArcadeScene::ArcadeScene():ButtonOptionsScene({"Tetris", "Break Out!", "Asteroids", "!Pac-man"}, Color::Cyan()) {}

 void ArcadeScene::init() {
    std::vector<Button::ButtonAction> actions;

    actions.push_back([this]{
        App::Singleton().pushScene(getScene(TETRIS));
    });

     actions.push_back([this]{
         App::Singleton().pushScene(getScene(BREAK_OUT));
     });

     actions.push_back([this]{
         App::Singleton().pushScene(getScene(ASTEROIDS));
     });

     actions.push_back([this]{
         App::Singleton().pushScene(getScene(PACMAN));
     });

     setButtonActions(actions);

     ButtonOptionsScene::init();


}

 void ArcadeScene::update(uint32_t dt) {
}

 void ArcadeScene::draw(Screen& theScreen) {
    ButtonOptionsScene::draw(theScreen);

}

 const std::string& ArcadeScene::getSceneName() const {
    static std::string sceneName = "Arcade";
    return sceneName;
}


std::unique_ptr<Scene> ArcadeScene::getScene(eGame game) {
    switch(game) {
        case TETRIS: {
            std::unique_ptr<Tetris> tetrisGame = std::make_unique<Tetris>();

            std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));

            return tetrisScene;
        }

        case BREAK_OUT: {
            std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();

            std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

            return breakoutScene;
        }

        case ASTEROIDS: {
            std::unique_ptr<Asteroids> asteroidsGame = std::make_unique<Asteroids>();

            std::unique_ptr<GameScene> asteroidsScene = std::make_unique<GameScene>(std::move(asteroidsGame));

            return asteroidsScene;
        }

        case PACMAN: {
            return std::make_unique<PacmanStartScene>();
        }
    }

    std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();
    return notImplementedScene;
}