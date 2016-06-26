/**
 * @class Waves
 *
 * @brief Perlin waves visualization
 *
 * Uses a 2d texture generated from perlin noise to displace a mesh/plane
 * Most of the work happens in the wave.frag/wave.vert shaders
 * For placement, relies on using easyCam and changing the viewport location
 * to deal with perspective issues
 */

#pragma once
#include "ofMain.h"
#include "widget.h"
#include "animated.h"
#include <vector>

class Waves : public Animated, public Widget {
    public:
        Waves();

        void update();
        void draw();

        /// Set the camera distance to the drawing plane (XY).
        void setCameraDistance(int distance);

        /// Get the position of the update line.
        int getUpdatePosition();

        void setSize(int width, int height);

    private:
        /**
         * @brief Initialize the displacement texture.
         *
         * @param descalar Divide the box size by this value to get
         *                 the texture size.
         */
        void initTexture(int descalar);

        /**
         * @brief Initialize the plane for solid waves.
         *        Requires the displacementTexture to be initialized.
         *
         * @param descalar Divide the box size by this value to get
         *                 the number of points per side.
         * @param zDisplacement The displacement between the point mesh and
         *                      the plane.
         */
        void initPlane(int descalar, int zDisplacement);

        /**
         * @brief Initialize the point mesh.
         *        Requires the displacementTexture to be initialized.
         *
         * @param spacing The distance between points of the mesh.
         */
        void initMesh(int spacing);

        /**
         * @brief Draw a corner at the given position.
         *
         * @param position The position of the corner, relative to the center
         *                 of the box.
         *                 The orientation is determined by the sign of the
         *                 (x, y, z) coordinates.
         */
        void drawCorner(ofPoint position);

        void updateDisplacementTexture();
        void drawBoxes();
        void drawCorners();
        void drawWaves();

        // The dimension of the side of the box (has a square base).
        float boxSide;
        // The height of the box.
        float boxHeight;
        // The length of the corner emphasis.
        float cornerSize;

        // Displacement scalers passed to the shader.
        float oldScale; // Scale of the previous frame (before the update line)
        float newScale; // Scale of the next frame (behind the update line)

        // The time base at position 0 of the waves visualization
        float baseTime;

        // The default orientation of the box.
        float rotateX;
        float rotateY;
        float rotateZ;

        // The rotation speed along Z axis.
        float rotateZRate;

        // The progress rate of the update sweep line.
        int updateSweepRate;

        // The distance of the camera to the drawing plane (XY).
        float cameraDistance;

        // Structures for waves visualization.
        ofMesh mesh;
        ofPlanePrimitive plane;

        ofShader waveShader;
        ofImage displacementTexture;
        ofEasyCam easyCam;
};
