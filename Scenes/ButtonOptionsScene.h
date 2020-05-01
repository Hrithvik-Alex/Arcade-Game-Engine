//
// Created by Hrithvik  Alex on 2020-04-28.
//

#ifndef LINES_BUTTONOPTIONSSCENE_H
#define LINES_BUTTONOPTIONSSCENE_H

#include "Scene.h"
#include "../App/Button.h"
#include <string>
#include <vector>

class Screen;

class ButtonOptionsScene: public Scene {
public:

    ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor);

    virtual void init() override;
    virtual void update(uint32_t dt) override;
    virtual void draw(Screen& theScreen) override;

    void setButtonActions(const std::vector<Button::ButtonAction>& buttonActions);

private:

    void setNextButtonHighlighted();
    void setPreviousButtonHighlighted();
    void executeCurrentButtonAction();
    void highlightCurrentButton();

    std::vector<Button> mButtons;
    int mHighlightedOption;

};


#endif //LINES_BUTTONOPTIONSSCENE_H
