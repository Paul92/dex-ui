#pragma once

#include "ofMain.h"
#include "base/widget.h"
#include "exceptions/outOfRange.h"
#include "utils/graphics-utils.h"

/**
 * @class Text
 *
 * @brief Wrapper for ofTrueTypeFont, with a string member.
 */
class Text : public Widget {

    public:
        Text(string text,  AnchorPosition anchor = TOP_LEFT,
             int size = 5, string font = MAIN_FONT);

        void setFont(int size, string font = MAIN_FONT);
        void setText(string text);
        void setSpaceSize(float size);
        float getSpaceSize();

        void draw() const;

    private:
        std::string text;
        ofTrueTypeFont ofFont;
};
