#include "animatedText.h"

AnimatedText::AnimatedText(std::string string, int fontSize,
                           AnchorPosition anchor) :
                 text(string, anchor, fontSize) {

    Widget::setSize(text.getWidth(), text.getHeight());

    setColor(COLOR_75);
    setFlickerParameters(5, 50);

    addEvent(AnimationEvent("intro", flickerDuration));
    addEvent(AnimationEvent("main"));
}

void::AnimatedText::setFont(int size, std::string font) {
    text.setFont(size, font);
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

    ofPushMatrix();
    {
        ofTranslate(getPosition().x, getPosition().y);
        if (currentEvent() == "delay") {
        } else if (currentEvent() == "intro") {
            float alpha = 255 * flicker(getTime(), flickerDuration, flickerRate);
            ofSetColor(color, alpha);
            text.draw();
        } else if (currentEvent() == "main") {
            ofSetColor(color, 255);
            text.draw();
        } else {
            throw new UnknownEvent();
        }
    }
    ofPopMatrix();
}

void AnimatedText::setSize(int width, int height) {
    Widget::setSize(width, 0);
    text.setSize(width, 0);
}

void AnimatedText::setText(std::string text) {
    this->text.setText(text);
    Widget::setSize(this->text.getWidth(), this->text.getHeight());
}

void AnimatedText::setSpaceSize(float size) {
    text.setSpaceSize(size);
    Widget::setSize(this->text.getWidth(), this->text.getHeight());
}

float AnimatedText::getSpaceSize() {
    return text.getSpaceSize();
}

