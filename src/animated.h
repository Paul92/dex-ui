#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"
#include "animationEvent.h"

/**
 * @class Animated
 *
 * @brief Base class for animated widgets.
 *
 * Provides routines for managing the events of an application.
 * Delays are introduced by having empty events.
 * It works by having an individual timer that counts the frames.
 */
class Animated {
    public:
        Animated();

        /// Update the timer and the current event, if necessary.
        void updateTime();

        /// Get the progress of the current event.
        int getTime();

        void addEvent(AnimationEvent event);
        void addEvent(AnimationEvent event, int index);

        void setEvents(vector<AnimationEvent> event);

        void update();

    protected:
        /// Updates the events of the components.
        virtual void updateDependencyEvents();

        std::string currentEvent();

    private:
        int currentEventIndex;
        float currentTime;
        std::vector<AnimationEvent> events;
};
