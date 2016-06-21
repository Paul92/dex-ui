#pragma once

#include "ofMain.h"

/**
 * @enum AnchorPosition
 *
 * The position of the anchor relative to the widget.
 */
enum AnchorPosition {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};

/**
 * @class Widget
 *
 * @brief Base class for widets used to handle common functionality.
 */
class Widget {
    private:
        int width;
        int height;
        ofPoint position;

    protected:
        AnchorPosition anchor;

    public:
        Widget(AnchorPosition anchor = TOP_LEFT);

        void setSize(int width, int height);
        void setPosition(ofPoint position);

        ofPoint getPosition() const;

        int getWidth() const;
        int getHeight() const;
};
