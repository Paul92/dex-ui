#pragma once

#include "ofMain.h"

/**
 * @class Text
 *
 * @brief Wrapper for ofTrueTypeFont, with a string member.
 */
class Text {

    public:
        Text(std::string text, string font, int size);

        /// Adjusted to draw from top left
        void drawString(ofPoint position);
        /// Adjusted to draw from top right
        void drawStringFromTopRight(ofPoint position);

        int getWidth();
        int getHeight();

    private:
        void setFont(string font, int size);

        ofTrueTypeFont ofFont;
        std::string text;
};
