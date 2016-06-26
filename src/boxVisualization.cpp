#include "boxVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

BoxVisualization::BoxVisualization(int width) :
    textRectangle("SYSTEM SUMMARY",
                  "WAVES VISUALIZATION",
                  "ANALYSIS OF\nSYSTEM UTILIZATION",
                  "HIGH LOAD\nALL ACTIVITY"),
    tline1(width, 40),
    tline2(width, 40) {

    setSize(width, 11 * GRID_SIZE);

    textRectangle.setCoordinates(ofRectangle(5, 5, getWidth() - 5, getHeight() - 18));

    // Set the color to all texts except the upper left one to COLOR_55.
    textRectangle.setColor(COLOR_55);
    textRectangle.setColor(COLOR_135, AnchorPosition::TOP_LEFT);

    textRectangle.addDelay(55, AnchorPosition::TOP_LEFT);
    textRectangle.addDelay(50, AnchorPosition::TOP_RIGHT);
    textRectangle.addDelay(45, AnchorPosition::BOTTOM_LEFT);
    textRectangle.addDelay(40, AnchorPosition::BOTTOM_RIGHT);

    waves.setSize(width, getHeight());
    waves.setCameraDistance(20000);

    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));
}

void BoxVisualization::update() {
    updateTime();

    if (currentEvent() == "intro")
          waves.setCameraDistance(easeOut(getTime(), 20000, 2400, 50));
}

void BoxVisualization::draw() {
    if (currentEvent() == "delay")
        return;

    update();

    ofPushMatrix();
    {
        ofTranslate(getPosition());

        // Intro
        tline1.draw();
        tline2.draw();

        waves.draw();

        textRectangle.draw();
    }
    ofPopMatrix();
}

