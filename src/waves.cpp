/*

   waves.h

   Perlin waves visualization
   Uses a 2d texture generated from perlin noise to displace a mesh/plane
   Most of the work happens in the wave.frag/wave.vert shaders
   For placement, relies on using easyCam and changing the viewport location
   to deal with perspective issues

*/
#include "waves.h"
#include "graphics-utils.h"

Waves::Waves() {
    // Initialize parameters

    setSize(300, 300);

    noise_scale = 150.0;
    cornerSize = 10.0;

    rotateX = 115;
    rotateY = 0;
    rotateZ = 0;

    rotateZ_rate = 4.0;
    update_sweep_rate = 4.0;


    // Load shaders
    waveShader.load("shadersGL3/wave");
    //  outlineShader.load("shadersGL3/outline");

    // Create displacement texture
    initTexture(5);

    // Create plane, if want solid waves
    initPlane(15, 20);

    // Create point mesh, map texture coordinates
    initMesh(4);

    camDist = 1500;
    easyCam.setTarget(ofVec3f(0,0,0));
    easyCam.setDistance(camDist);
//    easyCam.disableMouseInput();

    addEvent(AnimationEvent("main"));
}

void Waves::setSize(int width, int height) {
    Widget::setSize(width, height);
    boxSide = min(width, height);
    boxHeight = boxSide / 5;
}

void Waves::initTexture(int descalar) {
    texw = getWidth()/descalar;
    texh = getHeight()/descalar;
    displacementTexture.allocate(texw, texh, OF_IMAGE_GRAYSCALE);
}

void Waves::initPlane(int descalar, int z_displacement) {
    plane.set(getWidth(), getHeight(), getWidth()/descalar, getHeight()/descalar, OF_PRIMITIVE_TRIANGLES);
    plane.mapTexCoordsFromTexture(displacementTexture.getTextureReference());
    plane.setPosition(0,0,z_displacement);
}

void Waves::initMesh(int spacing) {
    mesh = ofMesh();
    mesh.setMode(OF_PRIMITIVE_POINTS);
    for (float y = 0; y < getHeight(); y += spacing) {
        for (float x = 0; x < getWidth(); x += spacing) {
            mesh.addVertex(ofPoint(x-getWidth()/2,y-getHeight()/2,0));
            mesh.addTexCoord(ofVec2f(x/getWidth()*texw,y/getHeight()*texh));
        }
    }
}

int Waves::getUpdatePosition() {
    // Only return 0 once, otherwise actions that occur at 0 will be repeated
    if (((int) getTime() % (int) (texw) == 0) && ((int) (getTime()/update_sweep_rate) % (int) (texw) == 0))
        return 0;
    return ((int) (getTime()/update_sweep_rate) % (int)(texw)) + 1;
}

void Waves::update() {
    updateTime();
    rotateZ += 1 / rotateZ_rate;

//    easyCam.setDistance(camDist);
//
//    //  zh = ofNoise(getTime()/100)*200;
//    //  noise_scale = ofNoise(getTime()/100+100)*getWidth()/2 + getWidth()/2;
//
//    if (getUpdatePosition() == 0) {
//        freezet = getTime();
//        old_zh = new_zh;
//        new_zh = zh * ((ofRandom(1)+0.3)*5);
//        //    cout << "old_zh " << old_zh << endl;
//        //    cout << "new_zh " << new_zh << endl;
//    }
//
//    // Update displacement texture
//    float coord_scale = 1/30.0;
//    float time_scale = 1/150.0;
//    unsigned char *pixels = displacementTexture.getPixels();
//    for (int y = 0; y < texh; y++) {
//        for (int x = 0; x < getUpdatePosition(); x++) {
//            int i = y * texw + x;
//            float n = ofNoise(x*coord_scale + freezet*time_scale,
//                    y*coord_scale + freezet*time_scale);
//            pixels[i] = 255*n;
//        }
//    }
//    displacementTexture.update();

    //  cout << getUpdatePosition() << endl;
}

void drawAxes() {
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofDrawLine(0, 0, 0, 100, 0, 0);
    ofPopStyle();

    ofPushStyle();
    ofSetColor(0, 255, 0);
    ofDrawLine(0, 0, 0, 0, 100, 0);
    ofPopStyle();

    ofPushStyle();
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, 0, 0, 0, 100);
    ofPopStyle();
}



void Waves::draw() {
    update();

    ofMatrix4x4 matrix = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);
    ofPoint viewportOrigin(getWidth() / 2, 0);
    viewportOrigin = viewportOrigin * matrix;


    easyCam.begin(ofRectangle(viewportOrigin, WIDTH, HEIGHT));

    ofPushMatrix();
    {
        ofRotateX(rotateX);
        ofRotateY(rotateY);
        ofRotateZ(rotateZ);

    drawAxes();
        ofPushStyle();
        {
            ofNoFill();
            ofSetColor(82, 104, 92, 25);
            ofDrawBox(0 , 0 , 0     , boxSide , boxSide , boxHeight*2);
            ofDrawBox(0 , 0 , -boxHeight+5 , boxSide , boxSide , 10);
            ofDrawBox(0 , 0 , boxHeight-5  , boxSide , boxSide , 10);
        }
        ofPopStyle();

        // Corners
        ofPushStyle();
        {
            ofSetColor(82, 104, 92, 255);
            for (int x = -1; x <= 1; x += 2) 
                for (int y = -1; y <= 1; y += 2)
                    for (int z = -1; z <= 1; z += 2)
                        drawCorner(ofPoint(x*(boxSide/2+5), y*(boxSide/2+5), z*(boxHeight+5)));
        }
        ofPopStyle();

        // Mesh
//        waveShader.begin();
//        waveShader.setUniform2f("scale", old_zh, new_zh);
//        waveShader.setUniform1f("updatePosition", getUpdatePosition());
//
//        ofNoFill();
//        ofSetColor(255, 255, 255);
//
//
//        waveShader.setUniform1f("alpha_adjust", 0.1);
//        //    plane.draw();
//        plane.drawWireframe();
//
//        waveShader.setUniform1f("alpha_adjust", 1);
//        mesh.draw();
//
//        waveShader.end();

        //    ofDisableDepthTest();
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

