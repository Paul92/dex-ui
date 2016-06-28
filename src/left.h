/*

   left.h

   Left panel of UI utils.
   Manages timeDisplay, boxVisualization, graphs, and two header objects.

*/
#pragma once
#include "ofMain.h"
#include "header.h"
#include "timeDisplay.h"
#include "boxVisualization.h"
#include "graph.h"
#include "noiseVisualization.h"
#include "animated.h"

class Left : public Widget, public Animated {

    public:
        Left(ofPoint position, int width);
        void draw();

    private:
        Header header;
        TimeDisplay timeDisplay;
        BoxVisualization boxVis;
        Graph core1;
        Graph core2;
        Graph core3;
        Graph core4;
        NoiseVisualization noiseVisualization;
        Header footer;

};
