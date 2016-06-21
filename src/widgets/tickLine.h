#pragma once

#include "ofMain.h"
#include "base/widget.h"
#include "utils/graphics-utils.h"

/**
 * @class TickLine
 *
 * Draw a line with ticks.
 */
class TickLine : public Widget {

    public:
        TickLine(int width, ofColor color = COLOR_LINE);

        void draw();

        /**
         * @brief Add a tick on the line.
         * @param position The x-position of the tick relative to the left
         *                 margin of the line.
         */
        void addTick(int position);

        /**
         * @brief Add a tick on the line.
         * @param position The relative position on the line, in range [0, 1],
         *                 where 0 is the leftmost margin and 1 is the
         *                 rightmost margin of the line.
         */
        void addTick(float position);

        void setColor(ofColor color);
        ofColor getColor();

    private:
        /**
         * @brief Draw a tick of size 2 * TICK_SIZE.
         * @param position The x-position of the tick relative to the left
         *                 margin of the line.
         */
        void drawTick(int position);

        /// The ticks present on the line.
        vector<float> ticks;

        ofColor color;
};

