#include "waves.h"
#include "graphics-utils.h"

Waves::Waves() {

    setSize(300, 300);

    baseTime = 0;
    oldScale = 0;
    newScale = 0;

    // Set the default orientation of the box.
    rotateX = 115;
    rotateY = 0;
    rotateZ = 0;

    // Set the animation speeds.
    rotateZRate = 4;
    updateSweepRate = 4;

    cornerSize = 12.0;

    // Load the shader.
    waveShader.load("shadersGL3/wave");

    // Set camera parameters.
    cameraDistance = 2500;
    easyCam.setDistance(cameraDistance);
    easyCam.disableMouseInput();

    addEvent(AnimationEvent("main"));
}

void Waves::setSize(int width, int height) {
    Widget::setSize(width, height);
    boxSide = min(width, height) * 2;
    boxHeight = boxSide / 7;

    initTexture(5);
    initPlane(10, 20);
    initMesh(10);
}

// Initialize displacement texture.
void Waves::initTexture(int descalar) {
    float textureWidth = boxSide / descalar;
    float textureHeight = boxSide / descalar;
    displacementTexture.allocate(textureWidth, textureHeight, OF_IMAGE_GRAYSCALE);
    displacementTexture.setColor(ofColor::black);
    displacementTexture.update();
}


// Initialize plane, for solid waves.
// Needs to have the displacementTexture allocated.
void Waves::initPlane(int descalar, int zDisplacement) {
    float numberOfPointsPerSide = boxSide / descalar;
    plane.set(boxSide, boxSide,
              numberOfPointsPerSide, numberOfPointsPerSide,
              OF_PRIMITIVE_TRIANGLES);
    plane.mapTexCoordsFromTexture(displacementTexture.getTexture());
    plane.setPosition(0, 0, zDisplacement);
}

// Initialize point mesh.
// Needs to have the displacementTexture allocated.
void Waves::initMesh(int spacing) {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for (float y = 0; y < boxSide; y += spacing) {
        for (float x = 0; x < boxSide; x += spacing) {
            // Add point to mesh.
            float pointX = ofMap(x, 0, boxSide, -boxSide / 2, boxSide / 2);
            float pointY = ofMap(y, 0, boxSide, -boxSide / 2, boxSide / 2);
            mesh.addVertex(ofPoint(pointX, pointY, 0));

            // Add texture to point.
            float texX = x / boxSide * displacementTexture.getWidth();
            float texY = y / boxSide * displacementTexture.getHeight();
            mesh.addTexCoord(ofVec2f(texX, texY));
        }
    }
}

int Waves::getUpdatePosition() {
    // Only return 0 once, otherwise actions that occur at 0 will be repeated
    if (((int)getTime() % (int)(displacementTexture.getWidth()) == 0)
     && ((int)getTime() / updateSweepRate % (int)displacementTexture.getWidth() == 0))
        return 0;
    return ((int)getTime() / updateSweepRate) % (int)displacementTexture.getWidth() + 1;
}

void Waves::updateDisplacementTexture() {
    float coordinateScaling = 1 / 30.0;
    float timeScaling = 1 / 150.0;

    unsigned char *pixels = displacementTexture.getPixels().getData();

    for (int y = 0; y < displacementTexture.getHeight(); y++) {
        for (int x = 0; x < getUpdatePosition(); x++) {
            int index = y * displacementTexture.getWidth() + x;
            float n = ofNoise(x * coordinateScaling + baseTime * timeScaling,
                              y * coordinateScaling + baseTime * timeScaling);
            pixels[index] = 255 * n;
        }
    }

    displacementTexture.update();
}

void Waves::update() {
    updateTime();

    if (rotateZRate)
        rotateZ += 1 / rotateZRate;

    easyCam.setDistance(cameraDistance);

    if (getUpdatePosition() == 0) {
        baseTime = getTime();
        oldScale = newScale;
        newScale = boxHeight * (ofRandom(1) + 0.3) * 5;
    }

    updateDisplacementTexture();
}

void Waves::drawBoxes() {
    ofPushStyle();
    {
        ofNoFill();
        ofSetColor(82, 104, 92, 25);
        ofDrawBox(0, 0, 0, boxSide, boxSide, boxHeight * 2);
        ofDrawBox(0, 0, -boxHeight + 5, boxSide, boxSide, 9);
        ofDrawBox(0, 0,  boxHeight - 5, boxSide, boxSide, 10);
    }
    ofPopStyle();
}

void Waves::drawCorners() {
    ofPushStyle();
    {
        ofSetColor(82, 104, 92, 255);
        for (int x = -1; x <= 1; x += 2) 
            for (int y = -1; y <= 1; y += 2)
                for (int z = -1; z <= 1; z += 2)
                    drawCorner(ofPoint(x * (boxSide / 2 + 7),
                                       y * (boxSide / 2 + 7),
                                       z * (boxHeight + 7)));
    }
    ofPopStyle();
}

void Waves::drawWaves() {
    waveShader.begin();
    waveShader.setUniform2f("scale", oldScale, newScale);
    waveShader.setUniform1f("updatePosition", getUpdatePosition());

    waveShader.setUniform1f("alpha_adjust", 1);
    displacementTexture.bind();
    mesh.draw();

    waveShader.setUniform1f("alpha_adjust", 0.1);
    plane.drawWireframe();
    displacementTexture.unbind();

    waveShader.end();
}

void Waves::draw() {
    update();

    // Get the global position of the viewport origin by transforming it
    // through the matrix stack.
    ofMatrix4x4 matrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    // The viewport origin relative to the widget's coordinate system.
    ofPoint viewportOrigin(getWidth() / 2, 0);
    // The viewport origin transformed through the global modelview matrix
    // (the widget's position is considered too).
    viewportOrigin = (viewportOrigin + getPosition()) * matrix;


    easyCam.begin(ofRectangle(viewportOrigin, WIDTH, HEIGHT));

    ofPushMatrix();
    {
        ofRotateX(rotateX);
        ofRotateY(rotateY);
        ofRotateZ(rotateZ);

        drawBoxes();
        drawCorners();
        drawWaves();
    }
    ofPopMatrix();

    easyCam.end();
}

int sign(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void Waves::drawCorner(ofPoint p) {
    ofDrawLine(p.x, p.y, p.z, p.x, p.y, p.z - sign(p.z) * cornerSize);
    ofDrawLine(p.x, p.y, p.z, p.x, p.y - sign(p.y) * cornerSize, p.z);
    ofDrawLine(p.x, p.y, p.z, p.x - sign(p.x) * cornerSize, p.y, p.z);
}

void Waves::setCameraDistance(int distance) {
    cameraDistance = distance;
}
