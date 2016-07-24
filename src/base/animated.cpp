#include "animated.h"
#include <stdexcept>
#include <iostream>

Animated::Animated() {
    initialTime = std::chrono::steady_clock::now();
    reset();
}

void Animated::updateAnimation() { }

std::string Animated::currentEvent() {
    if (currentEventIndex >= events.size()) {
        std::string errMessage = "Index of current event out of range ";
        throw std::range_error(errMessage);
    }

    if (events[currentEventIndex].isInfinite())
        return events[currentEventIndex].getLabel();

    auto currentDuration = std::chrono::steady_clock::now();
    auto timePassed = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(currentDuration - initialTime);
    
    if (timePassed.count() <= events[currentEventIndex].getDuration()) {
        return events[currentEventIndex].getLabel();
    } else if (timePassed.count() > events[currentEventIndex].getDuration()) {
        currentEventIndex++;
        return events[currentEventIndex].getLabel();
    }
}

int Animated::getTime() {
    currentTime = std::chrono::steady_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(currentTime - initialTime);
    return difference.count();
}

void Animated::addEvent(AnimationEvent event) {
    events.push_back(event);
}

void Animated::addEvent(AnimationEvent event, unsigned int index) {
    if (index >= events.size()) {
        std::string errorMessage = "Index exceeds the vector size in function ";
        errorMessage += __func__;
        throw std::out_of_range(errorMessage);
    } else {
        events.insert(events.begin() + index, event);
    }
}

void Animated::addDelay(int delay) {
    addEvent(AnimationEvent("delay", delay), 0);
}

void Animated::reset() {
    currentEventIndex = 0;
}

// Works by adding the durations of the events named "delay".
double Animated::getDelay() const {

    double totalDelay = 0;

    for (const auto &event : events)
        if (event.getLabel() == "delay")
            totalDelay += event.getDuration();

    return totalDelay;
}
