#include "noiseVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

NoiseVisualization::NoiseVisualization(int width) :
    upperTickLine(width, 40),
    lowerTickLine(width, 40),
    noise(width, 6 * GRID_SIZE + 1, 5)  // Add 1 to height to add another row
                                         // of pixels at the bottom
{
    setSize(width, 8 * GRID_SIZE);

    upperTickLine.setPosition(ofPoint(0, 0));
    lowerTickLine.setPosition(ofPoint(0, getHeight()));

    AnimatedText systemMap("SYSTEM MAP", 5);
    systemMap.setPosition(ofPoint(7, 6));
    systemMap.setFlickerParameters(5, 10);
    systemMap.setColor(COLOR_135);

    AnimatedText noiseVisualization("NOISE VISUALIZATION", 5,
                                    AnchorPosition::TOP_RIGHT);
    noiseVisualization.setPosition(ofPoint(getWidth() - 5, 6));
    noiseVisualization.setFlickerParameters(5, 10);
    noiseVisualization.setColor(COLOR_55);

    AnimatedText normal("NORMAL", 5, AnchorPosition::TOP_RIGHT);
    normal.setPosition(ofPoint(getWidth() - 5, getHeight() - 9));
    normal.setFlickerParameters(5, 10);
    normal.setColor(COLOR_55);

    texts.push_back(systemMap);
    texts.push_back(noiseVisualization);
    texts.push_back(normal);

    addEvent(AnimationEvent("intro", 100));
    addEvent(AnimationEvent("main"));
}

void NoiseVisualization::update() {
    updateAnimation();
}

void NoiseVisualization::draw() {
    update();
    ofPushMatrix();
    {
        ofTranslate(getPosition());

        upperTickLine.draw();
        lowerTickLine.draw();

        for (size_t index = 0; index < texts.size(); index++)
            texts[index].draw();

        // Draw noise, later in intro
        if (currentEvent() == "main" || getTime() > 100)
            noise.draw();
    }
    ofPopMatrix();
}

