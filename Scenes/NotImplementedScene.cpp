//
// Created by Hrithvik  Alex on 2020-04-28.
//

#include "NotImplementedScene.h"
#include "../App/App.h"
#include "../shapes/Rectangle.h"
#include "../Input/InputAction.h"
#include "../graphics/Screen.h"

void NotImplementedScene::init() {
    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            App::Singleton().popScene();
        }
    };

    gameController.addInputActionForKey(backAction);

}

void NotImplementedScene::update(uint32_t dt) {}

void NotImplementedScene::draw(Screen& theScreen) {
    const BitmapFont& font = App::Singleton().getFont();

    Rectangle rect = {Vec2D::Zero, App::Singleton().width(), App::Singleton().height()};

    Vec2D textDrawPosition;

    textDrawPosition = font.getDrawPosition(getSceneName(), rect, BFXA_CENTER, BFYA_CENTER);

    theScreen.Draw(font, getSceneName(), textDrawPosition, Color::Red());
}

const std::string& NotImplementedScene::getSceneName() const {
    static std::string name = "Not Implemented!";
    return name;
}