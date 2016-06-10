#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

class AnimatedTickLine : public Animated {
    public:
        AnimatedTickLine();
        void draw();
        void drawExtraTicks(float currentWidth, float centerX);

        float x;
        float y;
        float w;
        float duration;
        //  float delay;

        ofColor color;
        float alpha;

        vector<float> extraTicks;
};

AnimatedTickLine newTickLine(float x, float y, float w, float dur, float delay, ofColor color);

