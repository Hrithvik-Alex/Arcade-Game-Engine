//
// Created by Hrithvik  Alex on 2020-04-07.
//

#ifndef LINES_INPUTACTION_H
#define LINES_INPUTACTION_H

#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

using InputAction = std::function<void(uint32_t dt, InputState)>;

struct ButtonAction {
    InputKey key;
    InputAction action;
};

struct MousePosition {
    int32_t xPos, yPos;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& mousePosition)>;

struct MouseButtonAction {
    MouseButton mouseButton;
    MouseInputAction mouseInputAction;
};

#endif //LINES_INPUTACTION_H
