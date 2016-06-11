#include "animatedText.h"
#include "unknownEvent.h"

AnimatedText::AnimatedText(std::string string, int fontSize,
                           ofPoint position, bool fromRight) :
                 text(string, MAIN_FONT, fontSize),
                 Widget(text.getWidth(), text.getHeight(), position) {

    this->color = COLOR_LINE;
    this->fromRight = fromRight;

    this->flickerRate = 5;
    this->flickerDuration = 50;

    setPosition(position);

    addEvent(AnimationEvent("delay", 0));
    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));
}

void AnimatedText::setColor(ofColor color) {
    this->color = color;
}

void AnimatedText::setFlickerParameters(float rate, float duration) {
    this->flickerRate = rate;
    this->flickerDuration = duration;
}

void AnimatedText::draw() {
    updateTime();

    if (currentEvent() == "delay") {

    } else if (currentEvent() == "intro") {
        float alpha = 255 * flicker(getTime(), flickerDuration, flickerRate);
        ofSetColor(color, alpha);
        drawString();
    } else if (currentEvent() == "main") {
        ofSetColor(color, 255);
        drawString();
    } else {
        throw new UnknownEvent();
    }
}

void AnimatedText::drawString() {
    if (fromRight)
        text.drawStringFromTopRight(getPosition());
    else
        text.drawString(getPosition());
}

