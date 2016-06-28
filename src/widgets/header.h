/*

   header.h

   The status bar/header that goes on top of left, term, right

*/

#pragma once
#include "ofMain.h"
#include "base/animated.h"
#include "base/widget.h"
#include "widgets/animatedTickLine.h"
#include "widgets/textRectangle.h"

/**
 * @class Header
 *
 * @brief Class to represent a line header used for status bar.
 *
 * It is composed from a line with four text elements:
 *
 * upperLeftText                                   upperRightText
 * --------------------------------------------------------------
 * lowerLeftText                                   lowerRightText
 */
class Header : public Widget, public Animated {

    public:
        Header(int length, const TextRectangle &texts);
        void draw();

        void setSize(float width);
        void setColor(ofColor color);

    private:

        TextRectangle textRectangle;
        AnimatedTickLine line;
};

