//
// Created by Hrithvik  Alex on 2020-05-06.
//

#ifndef LINES_SCORE_H
#define LINES_SCORE_H


#include "../graphics/BitmapFont.h"
#include "../shapes/Rectangle.h"

class Screen;

class Score {
public:

    Score(Rectangle rect, const BitmapFont& bitmapFont);

    void draw(Screen& screen);

    inline void addToScore(int points) {mScore += points;}
    inline void resetScore() {mScore = 0;}

private:
    int mScore;
    const BitmapFont& mBitmapFont;
    Rectangle mBBox;

};


#endif //LINES_SCORE_H
