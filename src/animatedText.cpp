#include "animatedText.h"

AnimatedText::AnimatedText() {
    x = 0;
    y = 0;
    duration = 50;
    delay = 0;
    rate = 5;
    color = COLOR_LINE;
    fromRight = false;

    newEvent(0, 300, 0, 1); // intro
    newEvent(0, -1, 1, 1); // main
}

void AnimatedText::draw() {
    updateTime();

    if (getTime() < 0)
        return;

    if (currentEvent.id == 0) {
        // Intro
        float alpha = 255*flicker(getTime(), duration, rate);
        ofSetColor(color, alpha);
        drawString();
    } else{
        // Main
        ofSetColor(color, 255);
        drawString();
    }
}

void AnimatedText::setText(string fontPath, int size) {
    text.setFont(fontPath, size);
}

void AnimatedText::drawString() {
    if (fromRight)
        text.drawStringFromTopRight(s, x, y);
    else
        text.drawString(s, x, y);
}

AnimatedText newText(string s, int fontSize, float x, float y, float dur, float delay, ofColor color, bool fromRight) {
    AnimatedText newText = AnimatedText();
    newText.setText(MAIN_FONT, fontSize);
    newText.s = s;
    newText.fromRight = fromRight;
    newText.color = color;
    newText.duration = dur;
    newText.setDelay(delay);
    newText.x = x;
    newText.y = y;
    return newText;
}
