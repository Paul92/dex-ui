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
        textRectangle.addDelay(55);
        textRectangle.setCoordinates(ofRectangle(5, 5, getWidth() - 5, getHeight() - 18));

//
  waves = Waves();
//  waves.setPos(ofPoint(285,375));
//  
//  
//  int textDelay = -55;
//  // Top Left
//  texts.push_back(newText("SYSTEM SUMMARY", 5,
//                          5, 7,
//                          10, delay+textDelay,
//                          COLOR_135,
//                          false));
//  // Top Right
//  texts.push_back(newText("WAVES VISUALIZATION", 5,
//                          w-5, 7,
//                          10, delay+textDelay-5,
//                          COLOR_55,
//                          true));
//  // Bottom Right
//  texts.push_back(newText("HIGH LOAD", 5,
//                          w-5, h-18,
//                          10, delay+textDelay-10,
//                          COLOR_55,
//                          true));
//  texts.push_back(newText("ALL ACTIVITY", 5,
//                          w-4, h-11,
//                          10, delay+textDelay-10,
//                          COLOR_55,
//                          true));
//  // Bottom Left
//  texts.push_back(newText("ANALYSIS OF", 5,
//                          5,h-18,
//                          10, delay+textDelay-15,
//                          COLOR_55,
//                          false));
//  texts.push_back(newText("SYSTEM UTILIZATION", 5,
//                          5,h-11,
//                          10, delay+textDelay-15,
//                          COLOR_55,
//                          false));
//  
//  // Animation settings
    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));
}

void BoxVisualization::draw() {
    updateTime();
    ofPushMatrix();
    {
        ofTranslate(getPosition());

        // Intro
        tline1.draw();
        tline2.draw();

//        if (currentEvent() == "intro" && getTime() > 0)
//              waves.camDist = easeOut(getTime(), 20000, 2400, 50);

//        if (getTime() > 0)
              waves.draw();

        textRectangle.draw();
    }
    ofPopMatrix();
}

