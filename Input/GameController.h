//
// Created by Hrithvik  Alex on 2020-04-07.
//

#ifndef LINES_GAMECONTROLLER_H
#define LINES_GAMECONTROLLER_H

#include "InputAction.h"
#include <vector>

class GameController {
public:
    GameController();
    InputAction getActionForKey(InputKey key);
    void addInputActionForKey(const ButtonAction& buttonAction);
    void clearAll();

    static bool IsPressed(InputState state);
    static bool IsReleased(InputState state);
    static InputKey ActionKey();
    static InputKey DKey();
    static InputKey CancelKey();
    static InputKey ResetKey();
    static InputKey LeftKey();
    static InputKey RightKey();
    static InputKey UpKey();
    static InputKey DownKey();

    inline const MouseMovedAction& getMouseMovedAction() {return mMouseMovedAction;}
    inline void setMouseMovedAction(const MouseMovedAction& mouseMovedAction) {mMouseMovedAction = mouseMovedAction;}

    MouseInputAction getMouseButtonActionForButton(MouseButton button);
    void addMouseButtonAction(const MouseButtonAction& mouseButtonAction);

    static MouseButton LeftMouseButton();
    static MouseButton RightMouseButton();

private:
    std::vector<ButtonAction> mButtonActions;
    std::vector<MouseButtonAction> mMouseButtonActions;
    MouseMovedAction mMouseMovedAction;

};

#endif //LINES_GAMECONTROLLER_H
