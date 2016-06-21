#pragma once

#include <vector>

#include "ofMain.h"
#include "utils/graphics-utils.h"
#include "utils/easing-utils.h"
#include "base/animated.h"
#include "base/widget.h"
#include "widgets/tickLine.h"

/**
 * @class Draw a line with ticks.
 *
 * The initialisation animation is done by expanding from the middle to the
 * final width.
 */
class AnimatedTickLine : public Animated, public Widget {
    public:
        AnimatedTickLine(int width, int introDuration = 50, int delay = 0,
                         ofColor color = COLOR_LINE);

        void setColor(ofColor color);

        void addTick(int position);

        void draw();

    private:
        TickLine tickLine;
        float introDuration;
};

