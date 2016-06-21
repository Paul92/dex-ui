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
    freezet = 0;

    setSize(300, 300);

    zh = getWidth()/6;
    old_zh = getWidth()/6;
    new_zh = getWidth()/6;
    noise_scale = 150.0;

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

    camDist = 2400;
    view = ofPoint(0,0);
    easyCam = ofEasyCam();
    easyCam.setTarget(ofVec3f(0,0,0));
    easyCam.setDistance(camDist);
    easyCam.disableMouseInput();

    addEvent(AnimationEvent("main"));
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

void Waves::setPosition(ofPoint position) {
    Waves::setPosition(position);
    view.x = -WIDTH/2 + position.x;
    view.y = -HEIGHT/2 + position.y;
}

int Waves::getUpdatePosition() {
    // Only return 0 once, otherwise actions that occur at 0 will be repeated
    if (((int) getTime() % (int) (texw) == 0) && ((int) (getTime()/update_sweep_rate) % (int) (texw) == 0))
        return 0;
    return ((int) (getTime()/update_sweep_rate) % (int)(texw)) + 1;
}

void Waves::update() {
    updateTime();
//    //  rotateX = getTime()/3;
//    rotateZ += 1/rotateZ_rate;
//
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

void Waves::draw() {
    update();

    easyCam.begin(ofRectangle(view.x, view.y, WIDTH, HEIGHT));

    ofPushMatrix();
    {
        ofTranslate(getPosition());
        ofRotateX(rotateX);
        ofRotateY(rotateY);
        ofRotateZ(rotateZ);

        ofPushStyle();
        {
            ofNoFill();
            ofSetColor(82, 104, 92, 25);
            ofDrawBox(0, 0, 0, getWidth(), getHeight(), zh * 2);
            ofDrawBox(0, 0, -zh + 5, getWidth(), getHeight(), 10);
            ofDrawBox(0, 0,  zh - 5, getWidth(), getHeight(), 10);
        }
        ofPopStyle();

        // Corners
        ofSetColor(82, 104, 92, 255);

        for (int x = -1; x <= 1; x += 2)
            for (int y = -1; y <= 1; y += 2)
                for (int z = -1; z <= 1; z += 2)
                    drawCorner(ofPoint(x * (getWidth() / 2 + 10),
                                       y * (getHeight() / 2 + 10),
                                       z * (zh + 10)));

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

    //  ofSetColor(255, 255, 255);
    //  ofRect(ofGetMouseX(), ofGetMouseY(), 10, 10);
}

int Waves::sign(float x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void Waves::drawCorner(ofPoint p) {
    float pl = 10.0;
    ofLine(p.x, p.y, p.z, p.x, p.y, p.z-sign(p.z)*pl);
    ofLine(p.x, p.y, p.z, p.x, p.y-sign(p.y)*pl, p.z);
    ofLine(p.x, p.y, p.z, p.x-sign(p.x)*pl, p.y, p.z);
}

