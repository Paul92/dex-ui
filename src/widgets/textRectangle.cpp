#include "textRectangle.h"

TextRectangle::TextRectangle(string upperLeftText, string upperRightText,
                             string lowerLeftText, string lowerRightText,
                             int textSize, string font) :
    upperLeftText(upperLeftText, textSize, TOP_LEFT),
    lowerLeftText(lowerLeftText, textSize, BOTTOM_LEFT),
    upperRightText(upperRightText, textSize, TOP_RIGHT),
    lowerRightText(lowerRightText, textSize, BOTTOM_RIGHT) {

}

void TextRectangle::setCoordinates(ofRectangle rectangle) {
    upperLeftText.setPosition(ofPoint(0, 0));
    lowerLeftText.setPosition(ofPoint(0, rectangle.getHeight()));
    upperRightText.setPosition(ofPoint(rectangle.getWidth(), 0));
    lowerRightText.setPosition(ofPoint(rectangle.getWidth(), rectangle.getHeight()));

    setSize(rectangle.getWidth(), rectangle.getHeight());
    setPosition(rectangle.getPosition());
}

void TextRectangle::addDelay(int delay) {
    upperLeftText.addDelay(delay);
    lowerLeftText.addDelay(delay);
    upperRightText.addDelay(delay);
    lowerRightText.addDelay(delay);
}

void TextRectangle::draw() {
    ofPushMatrix();

    ofTranslate(getPosition());

    upperLeftText.draw();
    lowerLeftText.draw();
    upperRightText.draw();
    lowerRightText.draw();

    ofPopMatrix();
}

void TextRectangle::setColor(ofColor color) {
    upperLeftText.setColor(color);
    lowerLeftText.setColor(color);
    upperRightText.setColor(color);
    lowerRightText.setColor(color);
}

void TextRectangle::setFont(int size, std::string font) {
    upperLeftText.setFont(size, font);
    lowerLeftText.setFont(size, font);
    upperRightText.setFont(size, font);
    lowerRightText.setFont(size, font);
}

