#include "text.h"

void Text::setFont(string font, int size) {
    ofFont.loadFont(font, size, true, true);
}

Text::Text(std::string text, string font, int size) {
    this->text = text;
    setFont(font, size);
}

void Text::drawString(ofPoint position) {
    ofFont.drawString(text, position.x, position.y + ofFont.stringHeight(text));
}

void Text::drawStringFromTopRight(ofPoint position) {
    ofFont.drawString(text,
                      position.x - ofFont.stringWidth(text),
                      position.y + ofFont.stringHeight(text));
}

int Text::getWidth() {
    return ofFont.stringWidth(text);
}

int Text::getHeight() {
    return ofFont.stringHeight(text);
}
