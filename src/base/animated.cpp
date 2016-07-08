#include "animated.h"
#include <stdexcept>

Animated::Animated() {
    reset();
}

void Animated::updateAnimation() {
    if (currentEventIndex >= events.size()) {
        std::string message = "Current event not found in function ";
        message += __func__;
        throw std::range_error(message);
    }

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

void Animated::addEvent(AnimationEvent event, unsigned int index) {
    if (index >= events.size()) {
        std::string errorMessage = "Index exceeds the vector size in function ";
        errorMessage += __func__;
        throw std::out_of_range(errorMessage);
    } else {
        events.insert(events.begin() + index, event);
        reset();
    }
}

void Animated::addDelay(int delay) {
    addEvent(AnimationEvent("delay", delay), 0);
}

void Animated::reset() {
    currentTime = 0;
    currentEventIndex = 0;
}

// Works by adding the durations of the events named "delay".
float Animated::getDelay() {

    float totalDelay = 0;

    for (size_t index = 0; index < events.size(); index++)
        if (events[index].getLabel() == "delay")
            totalDelay += events[index].getDuration();

    return totalDelay;
}
