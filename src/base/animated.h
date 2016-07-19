#pragma once

#include <vector>

#include "animationEvent.h"

#include<ctime>
#include<ratio>
#include<chrono>

using namespace std::chrono;

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
        void updateAnimation();

        /// Get the progress of the current event.
        int getTime();

        /// Add event at the end of the current list of events.
        void addEvent(AnimationEvent event);

        /**
         * @brief Add event at given position.
         * @param The position before which the element is inserted.
         * @throws out_of_range If value of index is negative.
         * @throws bad_alloc From std::vector::insert() if the allocation does
         *                   not succeed.
         */
        void addEvent(AnimationEvent event, unsigned int index);

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

        ///  The initial time of an event.
        steady_clock::time_point initialTime;

        /// The list of events.
        std::vector<AnimationEvent> events;
};

