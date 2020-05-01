//
// Created by Hrithvik  Alex on 2020-04-28.
//

#include "ButtonOptionsScene.h"
#include "../App/App.h"
#include "../graphics/BitmapFont.h"
#include "../Utils/utils.h"
#include "../graphics/Screen.h"

ButtonOptionsScene::ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor):
mHighlightedOption(0)
{
    const BitmapFont& font = App::Singleton().getFont();

    for(size_t i = 0; i <  optionNames.size(); ++i) {
        mButtons.push_back(Button(font, textColor));
        mButtons.back().setButtonText(optionNames[i]);
    }

    if(optionNames.size() > 0) {
        mButtons[mHighlightedOption].setHighlighted(true);
    }
}

void ButtonOptionsScene::init() {
    ButtonAction upAction;
    upAction.key = GameController::UpKey();
    upAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            setPreviousButtonHighlighted();
        }
    };

    gameController.addInputActionForKey(upAction);

    ButtonAction downAction;
    downAction.key = GameController::DownKey();
    downAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            setNextButtonHighlighted();
        }
    };

    gameController.addInputActionForKey(downAction);

    ButtonAction acceptAction;
    acceptAction.key = GameController::ActionKey();
    acceptAction.action = [this](uint32_t dt, InputState state) {
        if(GameController::IsPressed(state)) {
            executeCurrentButtonAction();
        }
    };

    gameController.addInputActionForKey(acceptAction);

    uint32_t height = App::Singleton().height();
    uint32_t width = App::Singleton().width();

    const BitmapFont& font = App::Singleton().getFont();

    Size fontSize = font.getSizeOf(mButtons[0].getButtonText());

    const int BUTTON_PAD = 10;

    unsigned int buttonHeight = fontSize.height + BUTTON_PAD * 2;

    uint32_t maxButtonWidth = fontSize.width;

    for(const auto& button : mButtons) {
        Size s = font.getSizeOf(button.getButtonText());

        if(s.width > maxButtonWidth) {
            maxButtonWidth = s.width;
        }
    }

    maxButtonWidth += BUTTON_PAD*2;

    const uint32_t Y_PAD = 1;

    uint32_t yOffset = height/2 - ((buttonHeight+Y_PAD) * static_cast<uint32_t>(mButtons.size()))/2;

    for(auto& button : mButtons) {
        button.init(Vec2D(width/2-maxButtonWidth/2, yOffset), maxButtonWidth,buttonHeight);

        yOffset += buttonHeight + Y_PAD;
    }
    mButtons[mHighlightedOption].setHighlighted(true);

}

void ButtonOptionsScene::update(uint32_t dt) {}

void ButtonOptionsScene::draw(Screen& theScreen) {
    for(auto& button: mButtons) {
        button.draw(theScreen);
    }
}

void ButtonOptionsScene::setButtonActions(const std::vector<Button::ButtonAction>& buttonActions) {
    for(size_t i = 0; i < mButtons.size(); ++i) {
        mButtons[i].setButtonAction(buttonActions[i]);
    }
}

void ButtonOptionsScene::setNextButtonHighlighted() {
    mHighlightedOption = (mHighlightedOption + 1) % mButtons.size();

    highlightCurrentButton();
}

void ButtonOptionsScene::setPreviousButtonHighlighted() {
    mHighlightedOption = (mHighlightedOption + mButtons.size() - 1) % mButtons.size();

    highlightCurrentButton();
}

void ButtonOptionsScene::executeCurrentButtonAction() {
    mButtons[mHighlightedOption].executeAction();
}

void ButtonOptionsScene::highlightCurrentButton() {
    for(auto& button: mButtons) {
        button.setHighlighted(false);
    }
    mButtons[mHighlightedOption].setHighlighted(true);
}
