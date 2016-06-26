#pragma once

#include <string>

#include "widgets/animatedText.h"

/**
 * @class TextRectangle
 *
 * @brief Class to draw 4 texts placed in the corners of a rectangle.
 */
class TextRectangle : public Widget, public Animated {
    private:
        AnimatedText upperLeftText;
        AnimatedText lowerLeftText;
        AnimatedText upperRightText;
        AnimatedText lowerRightText;

    public:
        TextRectangle(std::string upperLeftText,  std::string lowerLeftText,
                      std::string upperRightText, std::string lowerRightText,
                      int textSize = 5, string font = MAIN_FONT);

        void addDelay(int delay);

        void setCoordinates(ofRectangle rectangle);

        void draw();

        void setColor(ofColor color);

        void setFont(int size, std::string font = MAIN_FONT);
};

