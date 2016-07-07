#include "animatedTickLine.h"

AnimatedTickLine::AnimatedTickLine(int width, int introDuration,
                                   int delay, ofColor color) :
              tickLine(width, color) {

    this->introDuration = introDuration;

    Widget::setSize(width, 0);

    addEvent(AnimationEvent("intro", this->introDuration));
    addEvent(AnimationEvent("main"));
}

void AnimatedTickLine::draw() {
    updateAnimation();

    ofPushMatrix();
    {
        ofTranslate(getPosition().x, getPosition().y);

        if (currentEvent() == "intro") {
            float currentWidth = easeInOut(getTime(), 0, getWidth(), introDuration);
            float lineStart = getPosition().x + (getWidth() - currentWidth) / 2;
            tickLine.setPosition(ofPoint(lineStart, 0));
            tickLine.setSize(currentWidth, 0);
        } else if (currentEvent() == "main") {
            tickLine.setSize(getWidth(), 0);
        }
        tickLine.draw();
    }
    ofPopMatrix();
}

void AnimatedTickLine::setColor(ofColor color) {
    tickLine.setColor(color);
}

void AnimatedTickLine::addTick(int position) {
    tickLine.addTick(position);
}

