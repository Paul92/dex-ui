#pragma once

#include "ofMain.h"
#include "base/animated.h"
#include "base/widget.h"
#include "utils/easing-utils.h"
#include "widgets/text.h"
#include "exceptions/unknownEvent.h"

/**
 * @class AnimatedText
 *
 * @brief Class to draw animated texts.
 *
 * The drawn text has a short flicker created by varying alpha at the
 * beginning.
 */
class AnimatedText : public Widget, public Animated {
    public:
        AnimatedText(string string, int fontSize,
                     AnchorPosition anchor = TOP_LEFT);

        /**
         * @brief Draws the text widget.
         * @throws UnknownEvent If there is an unexpected event in the
         *                      animation.
         */
        void draw();

        void setFlickerParameters(float rate, float duration);
        void setColor(ofColor color);
        void setFont(int size, std::string font);

        void setSize(int width, int height);
        void setSpaceSize(float size);

        void setText(std::string text);
        float getSpaceSize();

    private:
        float flickerDuration;
        float flickerRate;

        Text text;

        ofColor color;
};

