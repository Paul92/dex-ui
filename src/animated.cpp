#include "animated.h"
#include "easing-utils.h"

Animated::Animated() {
    currentTime = 0;
    currentEventIndex = 0;
}

void Animated::update() {
    // Loop or switch events if necessary
    if (!events[currentEventIndex].isInfinite() &&
                   currentTime + 1 >= events[currentEventIndex].getDuration()) {
        currentTime = 0;
        currentEventIndex++;
    }

    currentTime += 1;
}

std::string Animated::currentEvent() {
    return events[currentEventIndex].getLabel();
}

int Animated::getTime() {
    return currentTime;
}

void Animated::addEvent(AnimationEvent event) {
    events.push_back(event);
}

void Animated::addEvent(AnimationEvent event, int index) {
    events.insert(events.begin() + index, event);
}

void Animated::setEvents(std::vector<AnimationEvent> events) {
    this->events = events;
    currentEventIndex = 0;
    updateDependencyEvents();
}

void Animated::updateDependencyEvents() {
}

