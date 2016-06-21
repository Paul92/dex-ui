#include "text.h"
#include "utils/data-utils.h"

void Text::setFont(int size, std::string font) {
    ofFont.load(font, size);
}

void Text::setText(std::string text) {
    this->text = text;
    setSize(ofFont.stringWidth(text), ofFont.stringHeight(text));
}

Text::Text(std::string text, AnchorPosition anchor,
           int size, std::string font) {
    this->anchor = anchor;

    setFont(size, font);

    if (anchor == TOP_RIGHT || anchor == BOTTOM_RIGHT) {
        ofFont.setDirection(ofTtfSettings::RightToLeft);
        text = reverseLines(text);
    }

    setText(text);
}

void Text::draw() const {

    ofPoint drawPosition;

    switch (anchor) {
        case TOP_LEFT:
        case TOP_RIGHT:
            drawPosition = ofPoint(getPosition().x,
                                   getPosition().y + getHeight());
            break;
        case BOTTOM_LEFT:
        case BOTTOM_RIGHT:
            drawPosition = ofPoint(getPosition().x, getPosition().y);
            break;
        default:
            throw OutOfRange(anchor, __LINE__, "anchor");
    }
    ofFont.drawString(text, drawPosition.x, drawPosition.y);
}

void Text::setSpaceSize(float size) {
    ofFont.setSpaceSize(size);
    setSize(ofFont.stringWidth(text), ofFont.stringHeight(text));
}

float Text::getSpaceSize() {
    return ofFont.getSpaceSize();
}

