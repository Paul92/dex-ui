#include "left.h"
#include "textRectangle.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Left::Left(ofPoint position, int width) :
    header(width, TextRectangle("SYSTEM", "ALT PANEL", "", "")),
    timeDisplay(width),
    boxVis(width)
{
    Widget::setPosition(position);

    header.setPosition(ofPoint(0, 0));
    timeDisplay.setPosition(ofPoint(0, 2 * GRID_SIZE));

    boxVis.setPosition(ofPoint(0, 9*GRID_SIZE));
//
//    int graph_start=21;
//    g1.setPos(0, (graph_start)*GRID_SIZE);
//    g2.setPos(0, (graph_start+3)*GRID_SIZE);
//    g3.setPos(0, (graph_start+6)*GRID_SIZE);
//    g4.setPos(0, (graph_start+9)*GRID_SIZE);
//    g1.setName("CORE L1");
//    g2.setName("CORE L2");
//    g3.setName("CORE L3");
//    g4.setName("CORE L4");
//
//    noiseVis.setPos(0, 33*GRID_SIZE);
//
//    footer_len = 6*GRID_SIZE;
//    footer.setPos(w-footer_len, 41*GRID_SIZE);
//    footer.setSize(footer_len);
//    footer.setTextSize(7);
//    footer.br_text = "DEX UI";
//    footer.line.duration = 50;
//
//    // Animation settings
//    events.clear();
//    newEvent(0, 300, 0, 1); // intro
//    newEvent(0, -1, 1, 1); // main
//    currentEvent = events[0];

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
//        g1.draw();
//        g2.draw();
//        g3.draw();
//        g4.draw();
//        noiseVis.draw();
//        footer.draw();
    }
    ofPopMatrix();
}

