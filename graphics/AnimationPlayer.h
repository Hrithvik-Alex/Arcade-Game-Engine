//
// Created by Hrithvik  Alex on 2020-04-30.
//

#ifndef LINES_ANIMATIONPLAYER_H
#define LINES_ANIMATIONPLAYER_H

#include "Animation.h"
#include <stdint.h>
#include <vector>
#include <string>

class AnimationPlayer {
public:

    AnimationPlayer();
    bool init(const std::string& animationsPath);
    bool play(const std::string& animationName, bool looped);
    void pause();
    void stop();
    void update(uint32_t dt);
    AnimationFrame getCurrentAnimationFrame() const;

    inline bool isFinishedPlaying() const {return mIsFinishedPlaying;}
    inline uint32_t getCurrentFrameNumber() const {return mFrame;}

private:
    uint32_t mTime;
    std::vector<Animation> mAnimations;
    size_t mCurrentAnimation;
    uint32_t mFrame;

    bool mLooped;
    bool mIsPlaying;
    bool mIsFinishedPlaying;

};


#endif //LINES_ANIMATIONPLAYER_H
