#include "animated.h"

#include <iostream>

Animated::Animated() {
    reset();
}

void Animated::updateTime() {
    if (currentEventIndex >= events.size())
        throw NotFound();

    currentTime += 1;

    if (events[currentEventIndex].isInfinite())
        return;

    if (currentTime > events[currentEventIndex].getDuration()) {
        currentTime = 0;
        currentEventIndex++;
    }
}

std::string Animated::currentEvent() {
    return events[currentEventIndex].getLabel();
}

int Animated::getTime() {
    return currentTime;
}

void Animated::addEvent(AnimationEvent event) {
    events.push_back(event);
    reset();
}

void Animated::addEvent(AnimationEvent event, int index) {
    events.insert(events.begin() + index, event);
    reset();
}

void Animated::addDelay(int delay) {
    addEvent(AnimationEvent("delay", delay), 0);
}

void Animated::reset() {
    currentTime = 0;
    currentEventIndex = 0;
}

