//
// Created by Hrithvik  Alex on 2020-05-08.
//

#include "PacmanStartScene.h"
#include "../../App/App.h"
#include "../NotImplementedScene.h"
#include "../GameScene.h"
#include "../../Games/Pacman/PacmanGame.h"
#include <vector>
#include <memory>

PacmanStartScene::PacmanStartScene(): ButtonOptionsScene({"Play Game", "High Scores"}, Color::Yellow()) {}

void PacmanStartScene::init() {
    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            App::Singleton().popScene();
        }
    };

    gameController.addInputActionForKey(backAction);

    std::vector<Button::ButtonAction> actions;

    actions.push_back([this](){
        auto pacmanGame = std::make_unique<PacmanGame>();

        App::Singleton().pushScene(std::make_unique<GameScene>(std::move(pacmanGame)));
    });

    actions.push_back([this](){
        App::Singleton().pushScene(std::make_unique<NotImplementedScene>());
    });

    setButtonActions(actions);

    ButtonOptionsScene::init();
}

void PacmanStartScene::update(uint32_t dt) {

}

void PacmanStartScene::draw(Screen& theScreen) {
    ButtonOptionsScene::draw(theScreen);
}

const std::string& PacmanStartScene::getSceneName() const {
    static std::string name = "!Pacman Start!";
    return name;
}