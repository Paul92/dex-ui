#include "animationEvent.h"
#include "outOfRange.h"
#include "infiniteEvent.h"

void AnimationEvent::setInfinite() {
    duration = -1;
}

void AnimationEvent::setDuration(int duration) {
    if (duration < 0)
        throw new OutOfRange(duration, __LINE__, "duration");

    this->duration = duration;
}

AnimationEvent::AnimationEvent(std::string label, int duration) {
    this->label = label;

    if (duration == -1)
        setInfinite();
    else
        setDuration(duration);
}

int AnimationEvent::getDuration() {
    if (isInfinite())
        throw new InfiniteEvent();
    else
        return duration;
}

bool AnimationEvent::isInfinite() {
    return duration < 0;
}

std::string AnimationEvent::getLabel() {
    return label;
}

