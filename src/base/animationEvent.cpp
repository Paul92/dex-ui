#include "animationEvent.h"
#include "exceptions/outOfRange.h"
#include "exceptions/infiniteEvent.h"

void AnimationEvent::setInfinite() {
    duration = -1;
}

void AnimationEvent::setDuration(int duration) {
    if (duration < 0)
        throw new OutOfRange(duration, __LINE__, "duration");

    this->duration = duration;
}

AnimationEvent::AnimationEvent(std::string label) {
    this->label = label;
    setInfinite();
}

AnimationEvent::AnimationEvent(std::string label, int duration) {
    this->label = label;
    setDuration(duration);
}

int AnimationEvent::getDuration() const {
    if (isInfinite())
        throw new InfiniteEvent();
    else
        return duration;
}

bool AnimationEvent::isInfinite() const {
    return duration < 0;
}

std::string AnimationEvent::getLabel() const {
    return label;
}

