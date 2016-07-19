#include "animationEvent.h"
#include "exceptions/outOfRange.h"
#include "exceptions/infiniteEvent.h"

/*void AnimationEvent::setInfinite() {
    std::chrono::duration<int, std::milli> infiniteDuration(0);
    durationEvent = infiniteDuration;
}*/

/*void AnimationEvent::setDuration(int duration) {
    if (duration < 0)
        throw new OutOfRange(duration, __LINE__, "duration");

    this->duration = duration;
}*/

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

