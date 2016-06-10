#include "animatedTickLine.h"

AnimatedTickLine::AnimatedTickLine() {
    x = 0;
    y = 0;
    w = 240;
    duration = 50;
    delay = 0;
    color = COLOR_LINE;
    alpha = 255;

    newEvent(0, 300, 0, 1); // intro
    newEvent(0, -1, 1, 1); // main
}

void AnimatedTickLine::draw() {
    updateTime();

    if (currentEvent.id == 0 && getTime() > 0) {
        // Intro
        float temp_width = easeInOut(getTime(), 0, w, duration);
        float centerX = x+(w-temp_width)/2;
        ofSetColor(color, alpha);
        tick_line(centerX, centerX+temp_width, y);
        drawExtraTicks(temp_width, centerX);
    } else if (currentEvent.id == 1) {
        // Main
        ofSetColor(color, alpha);
        tick_line(x, x+w, y);
        drawExtraTicks(w,x);
    }
}

void AnimatedTickLine::drawExtraTicks(float currentWidth, float centerX) {
    // only for intro
    for (int i = 0; i < extraTicks.size(); i++) {
        float xpos = centerX + extraTicks[i] * currentWidth/w;
        tick(xpos, y);
    }
}

AnimatedTickLine newTickLine(float x, float y, float w, float dur, float delay, ofColor color) {
    AnimatedTickLine line = AnimatedTickLine();
    line.x = x;
    line.y = y;
    line.w = w;
    line.duration = dur;
    line.setDelay(delay);
    line.color = color;
    return line;
}

