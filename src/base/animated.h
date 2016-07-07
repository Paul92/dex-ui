#pragma once

#include <vector>

#include "base/animationEvent.h"

/**
 * @class Animated
 *
 * @brief Base class for animated widgets.
 *
 * Provides routines for managing the events of an application.
 * Delays are introduced by having empty events.
 *
 * It works by having an individual timer that counts the frames.
 * The class does not provide time keeping for infinite events.
 *
 * TODO: Add loops (i.e. cycle of multiple events).
 */
class Animated {
    protected:
        Animated();

        /**
         * @brief Update the timer and the current event, if necessary.
         * @throws NotFound If the next event is not found.
         */
        void updateTime();

        /// Get the progress of the current event.
        int getTime();

        /// Add event at the end of the current list of events.
        void addEvent(AnimationEvent event);

        /// Add event after the event at position index.
        void addEvent(AnimationEvent event, int index);

        /// Return the label of the current event.
        std::string currentEvent();

        /// Reset the current animation.
        void reset();

        /**
         * @brief Returns the total delay of the current animation.
         *
         * @throws InfiniteEvent if a delay event is improperly configured.
         */
        float getDelay();

    public:

        /// Adds delay to an animation by inserting a delay event at the
        /// beginning.
        void addDelay(int delay);

    private:
        /// The index of the current event.
        size_t currentEventIndex;

        /// The value of the internal time counter, in frames.
        int currentTime;

        /// The list of events.
        std::vector<AnimationEvent> events;
};

