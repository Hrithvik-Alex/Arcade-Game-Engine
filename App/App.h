//
// Created by Hrithvik  Alex on 2020-04-07.
//

#ifndef LINES_APP_H
#define LINES_APP_H

#include "../graphics/Screen.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "../Input/InputController.h"
#include "../graphics/BitmapFont.h"


struct SDL_Window;
class Scene;


class App {
public:
    static App& Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();

    inline uint32_t width() const {return mScreen.Width();}
    inline uint32_t height() const {return mScreen.Height();}

    void pushScene(std::unique_ptr<Scene> scene);
    void popScene();
    Scene* topScene();

    static const std::string& getBasePath();
    inline const BitmapFont& getFont() const {return mFont;}

private:
    Screen mScreen;
    SDL_Window* windowPtr;

    std::vector<std::unique_ptr<Scene>> sceneStack;
    InputController mInputController;

    BitmapFont mFont;
};

#endif //LINES_APP_H
