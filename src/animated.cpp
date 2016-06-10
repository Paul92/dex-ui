#include "animated.h"
#include "easing-utils.h"

Animated::Animated() {
    // Default variables and events
    // derived classes call automatically
    newEvent(0, -1, 0, 0);

    time = 0;
    delay = 0;
    currentEvent = events[0];
}

void Animated::updateTime() {
    // Loop or switch events if necessary
    if (currentEvent.duration != -1 && time + 1 >= currentEvent.duration) {
        time = 0;
        updateCurrentEvent();
    }

    time += 1;
}

void Animated::updateCurrentEvent() {
    int nextID = currentEvent.nextID;

    // If loop, don't change currentEvent
    if (nextID == currentEvent.id)
        return;

    // Otherwise find next id
    for (int i = 0; i < events.size(); i++) {
        animation_event_t e = events[i];
        if (e.id == currentEvent.nextID) {
            currentEvent = e;
            break;
        }
    }
}

float Animated::getTime() {
    return time+currentEvent.delay;
}

void Animated::newEvent(int delay, int duration, int id, int nextID) {
    animation_event_t e = animation_event_t();
    e.delay = delay;
    e.duration = duration;
    e.id = id;
    e.nextID = nextID;
    events.push_back(e);
}

void Animated::setEvents(vector<animation_event_t> events_) {
    events = events_;
    currentEvent = events[0];
    updateDependencyEvents();
}

void Animated::updateDependencyEvents() {
}

void Animated::setDelay(int delay_) {
    // By default update event0's delay, assumed to be intro
    events[0].delay = delay_;
    currentEvent = events[0];
    updateDependencyDelays(delay_);
}

int Animated::getDelay() {
    // By default return event0's delay
    return events[0].delay;
}

void Animated::updateDependencyDelays(int delay_) {
}

