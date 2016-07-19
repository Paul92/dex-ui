#include "animated.h"
#include <stdexcept>
#include <iostream>
using namespace std;
Animated::Animated() {
    initialTime = steady_clock::now();
    reset();
}

void Animated::updateAnimation() {
    /*if (currentEventIndex >= events.size()) {
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
    }*/
}

std::string Animated::currentEvent() {
    if (events[currentEventIndex].isInfinite())
        return "";

    steady_clock::time_point currentDuration = steady_clock::now();

    duration<int, std::milli>diff = duration_cast<duration<int, std::milli>>(currentDuration - initialTime);
    cout << "DINO ";
    if (diff.count() > events[currentEventIndex].getDuration()){
        currentEventIndex++;
        cout <<  "DINO ";
        return events[currentEventIndex].getLabel();
    }
}

int Animated::getTime() {
    return currentTime;
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
    currentTime = 0;
    currentEventIndex = 0;
}

// Works by adding the durations of the events named "delay".
float Animated::getDelay() {

    float totalDelay = 0;

    for (const auto &event:events)
        if (event.getLabel() == "delay")
            totalDelay += event.getDuration();

    return totalDelay;
}
