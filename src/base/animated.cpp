#include "animated.h"
#include <stdexcept>
#include <iostream>

Animated::Animated():initialTime(std::chrono::steady_clock::now()){
    reset();
}

void Animated::updateAnimation() { }

std::string Animated::currentEvent() {
    if (currentEventIndex >= events.size()) {
        throw std::range_error("Current event out of range. Does your animation had an infinite event at the end?");
    }

    if (events[currentEventIndex].isInfinite())
        return events[currentEventIndex].getLabel();

    auto currentTime = std::chrono::steady_clock::now();
    auto timePassedSinceAnimationStarted = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(currentTime - initialTime);
    int  timePassedSinceEventStarted = timePassedSinceAnimationStarted.count();

    for (decltype(events)::size_type index = 0; index < currentEventIndex; index++) {
        // Time passed since the current event started
        timePassedSinceEventStarted -= events[index].getDuration();
    }

    if (timePassedSinceEventStarted <= events[currentEventIndex].getDuration()) {
        return events[currentEventIndex].getLabel();
    } else if (timePassedSinceEventStarted > events[currentEventIndex].getDuration()) {
        currentEventIndex++;
        return events[currentEventIndex].getLabel();
    }
}

int Animated::getTime() {
    auto currentTime = std::chrono::steady_clock::now();
    auto timePassedSinceAnimationStarted = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(currentTime - initialTime);
    int timePassedSinceEventStarted = timePassedSinceAnimationStarted.count();

    for (decltype(events)::size_type index = 0; index < currentEventIndex; index++) {
        timePassedSinceEventStarted -= events[index].getDuration();
    }
    return timePassedSinceEventStarted;
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
