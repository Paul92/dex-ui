#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

#include "animated.h"
#include "widget.h"
#include "easing-utils.h"

/**
 * @class AnimatedText
 *
 * @brief Class to draw animated texts.
 */
class AnimatedText : public Widget, public Animated {
    public:
        AnimatedText(std::string text, int fontSize,
                     ofPoint position, bool fromRight = false);
        void draw();

        void setFlickerParameters(float rate, float duration);
        void setColor(ofColor color);

    private:
        float flickerDuration;
        float flickerRate;
        bool fromRight;

        ofColor color;

        Text text;

        void drawString();
};

