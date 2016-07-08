#include "components/noiseWindow.h"

NoiseWindow::NoiseWindow(int width, int height, int updateRate) {

    setSize(width, height);
    this->updateRate = updateRate;
    updatePosition = getWidth() - 5;
    noiseOffset = 0;

    noiseShader.load("shadersGL3/noise");

    noiseTexture.allocate(getWidth(), getHeight(), OF_IMAGE_GRAYSCALE);

    unsigned char *pixels = noiseTexture.getPixels().getData();
    memset(pixels, 0, getWidth() * getHeight());

    noiseTexture.update();

    addEvent(AnimationEvent("main"));
}

void NoiseWindow::update() {
    updateTime();

    if ((int)getTime() % updateRate == 0) {

        unsigned char *pixels = noiseTexture.getPixels().getData();

        for (int y = 0; y < noiseTexture.getHeight(); y += 5) {
            int index = y * getWidth() + updatePosition;
            float pixelValue = ofNoise((noiseOffset + y) / 50,
                                       (noiseOffset + updatePosition) / 50);
            pixels[index] = easeIn(pixelValue, 0, 255, 1);
        }

        for (int y = 0; y < noiseTexture.getHeight(); y += 5) {
            for (int x = 0; x < noiseTexture.getWidth(); x += 5) {
                if (x < updatePosition || x > updatePosition + 50) {
                    int index = y * getWidth() + x;
                    pixels[index] = max(pixels[index] - 3, 0);
                }
            }
        }
        noiseTexture.update();

        updatePosition -= 5;
        if (updatePosition < 0) {
            updatePosition = getWidth() - 5;
            noiseOffset += noiseOffset;
        }
    }
}

void NoiseWindow::draw() {
    update();
    noiseTexture.getTexture().bind();

    ofPushMatrix();
    {
        ofTranslate(0, GRID_SIZE);
        ofSetColor(COLOR_95);

        noiseShader.begin();
        ofFill();
        ofDrawRectangle(0, 0, getWidth(), getHeight());
        noiseShader.end();
    }
    ofPopMatrix();

    noiseTexture.getTexture().unbind();
}
