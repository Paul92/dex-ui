#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

class AnimatedText : public Animated {
    public:
        AnimatedText();
        void draw();
        void setText(string fontPath, int size);

        float x;
        float y;
        float duration;
        //  float delay;
        float rate;
        string s;
        bool fromRight;

        ofColor color;

        Text text;
    private:
        void drawString();
};

AnimatedText newText(string s, int fontSize, float x, float y, float dur, float delay, ofColor color, bool fromRight);
