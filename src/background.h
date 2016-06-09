#pragma once

#include "ofMain.h"

/**
 * @class Background
 *
 * @brief Class used to draw the background.
 *
 * This class draws the background of the application, visible below the
 * widgets. The default implementation uses a mesh to generate evenly spread
 * points, but it can easily be modified to add pictures and/or other patterns.
 */
class Background {
    public:
        Background();
        void draw(int alpha);

        /// The current alpha value of the grid.
        int currentGridAlpha;

        /// The number of points of the grid.
        int numberOfPoints;

        /// The grid datastructure.
        ofMesh gridMesh;

    private:
        /// Method used to update the alpha of the grid.
        void updateGridAlpha(int alpha);
};

