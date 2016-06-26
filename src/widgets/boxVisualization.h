/*
 
 boxVisualization.h
 
 Box/Waves visualization, in the style of Tron boardroom
 Is dependent on absolute positioning because of waves
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "waves.h"
#include "animated.h"
#include "animatedTickLine.h"
#include "animatedText.h"
#include "textRectangle.h"

#include <vector>

class BoxVisualization : public Animated, public Widget {

    public:
        BoxVisualization(int width);
        void draw();
        void update();

        Waves waves;

    private:
         TextRectangle textRectangle;
         AnimatedTickLine tline1;
         AnimatedTickLine tline2;
};

