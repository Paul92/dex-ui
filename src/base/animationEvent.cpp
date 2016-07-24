#include "animationEvent.h"
#include "exceptions/outOfRange.h"
#include "exceptions/infiniteEvent.h"

AnimationEvent::AnimationEvent(std::string label) {
    this->label = label;
    infinite = true;
}

AnimationEvent::AnimationEvent(std::string label, int milliseconds):
                duration(milliseconds) {
    this->label = label;
}

int AnimationEvent::getDuration() const {
    if (isInfinite())
        throw new InfiniteEvent();
    else
        return duration.count();
}

bool AnimationEvent::isInfinite() const {
    return infinite;
}

std::string AnimationEvent::getLabel() const {
    return label;
}

