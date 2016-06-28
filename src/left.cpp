#include "left.h"
#include "textRectangle.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Left::Left(ofPoint position, int width) :
    header(width, TextRectangle("SYSTEM", "ALT PANEL", "", "")),
    timeDisplay(width),
    boxVis(width),
    core1(width),
    core2(width),
    core3(width),
    core4(width),
    noiseVisualization(width),
    footer(6 * GRID_SIZE, TextRectangle("", "", "", "DEX UI"))
{
    Widget::setPosition(position);

    header.setPosition(ofPoint(0, 0));
    timeDisplay.setPosition(ofPoint(0, 2 * GRID_SIZE));

    boxVis.setPosition(ofPoint(0, 9*GRID_SIZE));

    int graph_start=21;
    core1.setPosition(ofPoint(0, (graph_start)*GRID_SIZE));
    core2.setPosition(ofPoint(0, (graph_start+3)*GRID_SIZE));
    core3.setPosition(ofPoint(0, (graph_start+6)*GRID_SIZE));
    core4.setPosition(ofPoint(0, (graph_start+9)*GRID_SIZE));
    core1.setName("CORE L1");
    core2.setName("CORE L2");
    core3.setName("CORE L3");
    core4.setName("CORE L4");

    noiseVisualization.setPosition(ofPoint(0, 33*GRID_SIZE));

    footer.setPosition(ofPoint(width - footer.getWidth(), 41 * GRID_SIZE));

//    footer.line.duration = 50;

    addEvent(AnimationEvent("delay", 0));
    addEvent(AnimationEvent("intro", 300));
    addEvent(AnimationEvent("main"));

}

void Left::draw() {
    updateTime();
    ofPushMatrix();
    {
        ofTranslate(getPosition().x, getPosition().y);

//        if (currentEvent.id == 0) {
//            // Intro
//            // Set header / footer colors
//
//            // Header
//            float headerAlpha = 0;
//            if (time+header.line.getDelay() > header.line.duration + 10)
//                headerAlpha = flicker(time+header.line.getDelay()-(header.line.duration + 10), 20, 5)*255;
//            header.setAlpha(255,headerAlpha);
//
//            // Footer
//            float footerAlpha = 0;
//            if (time+footer.line.getDelay() > footer.line.duration + 10)
//                footerAlpha = flicker(time+footer.line.getDelay()-(footer.line.duration + 10), 20, 5)*255;
//            footer.setAlpha(255,footerAlpha);
//        }
//
        header.draw();
        timeDisplay.draw();
        boxVis.draw();
        core1.draw();
        core2.draw();
        core3.draw();
        core4.draw();
        noiseVisualization.draw();
        footer.draw();
    }
    ofPopMatrix();
}

