/*

   timeDisplay.h

   Clock and system uptime-esque stuff on the left panel

*/

#pragma once


#include <time.h>
#include <string.h>
#include <vector>

#include "ofMain.h"
#include "base/widget.h"
#include "base/animated.h"
#include "widgets/animatedText.h"
#include "widgets/animatedTickLine.h"

class TimeDisplay : public Animated, public Widget {

    public:
        TimeDisplay(int width);
        void draw();

    private:
        time_t initialTime;
        time_t currentTime;
        struct tm *localizedTime;

        double secondsPassed; /// Seconds passed since the last update.

        AnimatedTickLine upperLine;
        AnimatedTickLine midLine;
        AnimatedTickLine lowerLine;

        AnimatedText mainTime;
        vector<AnimatedText> upperTexts;
        vector<AnimatedText> lowerTexts;

        void update();
        void updateClockTime();
        void updateStrings();

        void initializeLines();
        void initializeMainTime();
        void initializeTextArrays(int xPositions[4]);
        void initializeUpperTexts(int xPositions[4], std::string year);
        void initializeLowerTexts(int xPositions[4], std::string month);

        void updateMainTime();
        void updateUptime();
};

