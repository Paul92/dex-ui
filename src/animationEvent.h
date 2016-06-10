#pragma once

#include <string>

/**
 * @class AnimationEvent
 *
 * @brief Class used to represent an animation event in an animation.
 *
 * This class is used to represent parts of an animation, identified by a
 * label. The duration can be either finite (represented by a number) or
 * infinite (in a boolean).
 *
 * If an event has an infinite duration, it stops the progression to other
 * events (so it should be the last one).
 */
class AnimationEvent {
    private:
        int duration;
        std::string label;

        void setDuration(int duration);
        void setInfinite();

    public:
        AnimationEvent(std::string label, int duration = -1);

        int getDuration();
        bool isInfinite();
        std::string getLabel();
};
