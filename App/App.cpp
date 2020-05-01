//
// Created by Hrithvik  Alex on 2020-04-07.
//


#include "App.h"
#include "SDL.h"
#include <iostream>
#include <memory>
#include "../Scenes/ArcadeScene.h"
#include <cassert>


App& App::Singleton() {
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag) {

    if(!mFont.load("ArcadeFont")) {
        std::cout << "Could not load arcade font!" << std::endl;
        return false;
    }

    windowPtr = mScreen.Init(width,height,mag);
    std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
    pushScene(std::move(arcadeScene));

    //temp
//    {

//    }

    return windowPtr != nullptr;
}
void App::Run() {
    if (windowPtr) {

        bool run = true;

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;

        uint32_t dt = 10;
        uint32_t accumulator = 0;

        mInputController.init([&run](uint32_t dt, InputState state){
            run = false;
        });

        while(run) {

            currentTick = SDL_GetTicks();
            uint32_t frameTime = currentTick - lastTick;

            if (frameTime > 300) {
                frameTime = 300;
            }

            lastTick = currentTick;

            accumulator += frameTime;


            //Input
            mInputController.update(dt);

            Scene* topS = topScene();
            assert(topS && "where is top scene?");

            if(topS) {

                // update
                while (accumulator >= dt) {
                    //update current scene by acc / dt
                    topS->update(dt);
                    accumulator -= dt;
                }

                // Render bois
                topS->draw(mScreen);
            }
            mScreen.SwapScreen();
        }   
    }

}

void App::pushScene(std::unique_ptr<Scene> scene) {
    assert(scene && "where is scene?");
    if(scene) {
        scene->init();
        mInputController.setGameController(scene->getGameController());
        sceneStack.emplace_back(std::move(scene));
        SDL_SetWindowTitle(windowPtr, topScene()->getSceneName().c_str());
    }
}

void App::popScene() {
    if(sceneStack.size() > 1) {
        sceneStack.pop_back();
    }
    if(topScene()) {
        mInputController.setGameController(topScene()->getGameController());
        SDL_SetWindowTitle(windowPtr, topScene()->getSceneName().c_str());
    }
}

Scene* App::topScene() {
    if(sceneStack.empty()) {
        return nullptr;
    }

    return sceneStack.back().get();
}

 const std::string& App::getBasePath() {
    static std::string basePath = SDL_GetBasePath();

    return basePath;
}

