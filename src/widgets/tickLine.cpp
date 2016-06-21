#include "tickLine.h"

TickLine::TickLine(int width, ofColor color) {
    setSize(width, 0);
    setColor(color);

    addTick(0);
    addTick(width);
}

void TickLine::addTick(int position) {
    ticks.push_back((float)position / getWidth());
}

void TickLine::addTick(float position) {
    ticks.push_back(position);
}

ofColor TickLine::getColor() {
    return color;
}

void TickLine::setColor(ofColor color) {
    this->color = color;
}

void TickLine::drawTick(int position) {
    ofDrawLine(position + 0.5, TICK_SIZE + 0.5, position + 0.5, -TICK_SIZE + 0.5);
}

void TickLine::draw() {
    ofPushMatrix();
    {
        ofTranslate(getPosition());
        ofSetColor(color);

        ofDrawLine(0.5, 0.5, 0.5 + getWidth(), 0.5); 
        for (std::vector<float>::iterator tickIterator = ticks.begin();
                tickIterator != ticks.end(); tickIterator++)
            drawTick(*tickIterator * getWidth());
    }
    ofPopMatrix();
}

