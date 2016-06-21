#include "header.h"
#include "graphics-utils.h"

Header::Header(int width, const TextRectangle &texts) :
            textRectangle(texts),
            line(width, 50, 0, COLOR_LINE) {

        Widget::setSize(width, GRID_SIZE);
        textRectangle.setCoordinates(ofRectangle(5, 6, width - 8, GRID_SIZE));
        line.setPosition(ofPoint(0, GRID_SIZE));
}

void Header::draw() {
    ofPushMatrix();
    {
        ofTranslate(getPosition().x, getPosition().y);

        textRectangle.draw();
        line.draw();

    }
    ofPopMatrix();
}

void Header::setSize(float width) {
    Widget::setSize(width, GRID_SIZE);
    line.setSize(width, 0);
}

void Header::setTextSize(int size) {
    textRectangle.setFont(size);
}

void Header::setColor(ofColor color) {
    line.setColor(color);
    textRectangle.setColor(color);
}

