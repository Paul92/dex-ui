/**
 * @class Noise
 *
 * @brief Provides a rectangluar noise visualization.
 */

#pragma once
#include "ofMain.h"

#include "widget.h"
#include "animated.h"
#include "graphics-utils.h"
#include "easing-utils.h"

class NoiseWindow : public Widget, public Animated {
    private:

        int updateRate;
        int updatePosition;

        /// The texture generated using Perlin noise.
        ofImage noiseTexture;

        ofShader noiseShader;

        /// Offset of the snapshot in Perlin noise
        float noiseOffset;

        void update();

    public:
        /**
         * @brief Constructor for noise window.
         *
         * @param width The width of the window.
         * @param height The height of the window.
         * @param updateRate The progress rate of the updater line
         *                   (number of frames between succesive updates).
         */
        NoiseWindow(int width, int height, int updateRate);

        void draw();
};
