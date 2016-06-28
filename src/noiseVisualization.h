/**
 * @class NoiseVisualization
 *
 * @brief Noise visualization on bottom left panel
 *        Dots are generated from 2D Perlin noise
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "waves.h"
#include "animated.h"

#include "animatedText.h"
#include "animatedTickLine.h"
#include "noiseWindow.h"
#include "noiseWindow.h"

class NoiseVisualization : public Widget, public Animated {

    public:
        NoiseVisualization(int width);
        void update();
        void draw();
        void drawNoise();

        float noise_off;


    private:
        AnimatedTickLine upperTickLine;
        AnimatedTickLine lowerTickLine;
        NoiseWindow noise;
        vector<AnimatedText> texts;

        void initTexture(int descalar);
};
