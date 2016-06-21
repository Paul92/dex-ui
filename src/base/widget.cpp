#include "widget.h"

Widget::Widget(AnchorPosition anchor) {
    this->anchor = anchor;
    setPosition(ofPoint(0, 0));
    setSize(0, 0);
}

void Widget::setPosition(ofPoint position) {
    this->position = position;
}

ofPoint Widget::getPosition() const {
    return this->position;
}

int Widget::getWidth() const {
    return this->width;
}

int Widget::getHeight() const {
    return this->height;
}

void Widget::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

