#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

class Animated {
    public:
        Animated();
        void update();
        void updateTime();
        float getTime();

        void newEvent(int delay, int duration, int id, int nextID);

        void setEvents(vector<animation_event_t> events_);
        virtual void updateDependencyEvents();

        void setDelay(int delay_);
        int getDelay();
        virtual void updateDependencyDelays(int delay_);

        int currentEventIndex;
        animation_event_t currentEvent;

        vector<animation_event_t> events;
    protected:
        float time;
        float delay;
        void updateCurrentEvent();
};
