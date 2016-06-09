#include "background.h"
#include "graphics-utils.h"

Background::Background() {
    // Initialize member variables
    currentGridAlpha = 255;
    numberOfPoints   = 0;

    // Generate the background as points on a mesh
    gridMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int line = 0; line < WIDTH; line += GRID_SIZE){
        for (int column = 0; column < HEIGHT; column += GRID_SIZE){
            // Offset by 0.5 to ensure 1px points
            gridMesh.addVertex(ofPoint(line + 0.5, column + 0.5, 0));
            gridMesh.addColor(ofColor(255, 255, 255, currentGridAlpha));
            gridMesh.addIndex(numberOfPoints);
            numberOfPoints += 1;
        }
    }
}

// Draw the grid mesh at a given alpha.
// Avoid updating the grid's alpha value unless necessary.
void Background::draw(int alpha) {
    if (alpha != currentGridAlpha)
        updateGridAlpha(alpha);
    gridMesh.draw();
}

void Background::updateGridAlpha(int newAlpha) {
    currentGridAlpha = newAlpha;
    gridMesh.setColorForIndices(0, numberOfPoints,
                                ofColor(255, 255, 255, currentGridAlpha));
}

