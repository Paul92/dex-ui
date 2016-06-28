/*

   graph.h

   Simple spline graph visualization
   Used for displaying core's performance on left panel
   Has implementation of b-spline from aframes

*/

#pragma once
#include "ofMain.h"
#include "text.h"
#include "animated.h"
#include <vector>

#include "animatedText.h"
#include "animatedTickLine.h"

#include "base/animated.h"
#include "base/widget.h"

class Graph : public Animated, public Widget {

    public:
        Graph(int width);
        void update();
        void draw();

        void setName(std::string name);

        /// Flags that toggle the visibility of the rectangles.
        bool showRectangle1;
        bool showRectangle2;
        bool showRectangle3;

        /// The number of frames between 2 graph updates.
        int graphRefreshTime;

        /// The width of the graph line.
        float graphWidth;

        std::vector<ofPoint> graphPoints;

        /// The Y value of the new sample to be inserted in the graph.
        float nextSampleY;

        /// The distance between 2 consecutive datapoints of the graph.
        float pointDistance;

        /// The Y amplitude of the graph.
        float graphAmplitude;

        /// The duration of the line animation at the start.
        float introLinesDuration;
    private:
        /// Draw top/bottom lines.
        void drawLines();

        /// Draw the rectangles on the right.
        void drawRectangles();

        /// Draw the spline.
        void drawSpline();

        /// Draw the texts.
        void drawTexts();

        float rectangleWidth;

        void initializeTexts();
        std::vector<AnimatedText> texts;

        void bezierVertexFromDatapoints(ofPoint point1,
                                        ofPoint point2,
                                        ofPoint point3);

        ofPoint intermediatePoint(ofPoint p1, ofPoint p2, float distance);
};
