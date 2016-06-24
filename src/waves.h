#pragma once
#include "ofMain.h"
#include "widget.h"
#include "animated.h"
#include <vector>

class Waves : public Animated, public Widget {
    public:
        Waves();
        void initTexture(int descalar);
        void initPlane(int descalar, int z_displacement);
        void initMesh(int spacing);

        void update();
        void draw();

        int getUpdatePosition();

        void drawCorner(ofPoint p);

        void setSize(int width, int height);

        float boxSide;
        float boxHeight;
        float cornerSize;

        float noise_scale;

        float rotateX;
        float rotateY;
        float rotateZ;

        float rotateZ_rate;
        int update_sweep_rate;

        ofMesh mesh;
        ofPlanePrimitive plane;
        ofShader waveShader;
        ofShader outlineShader;
        ofImage displacementTexture;
        int texw, texh;

        ofEasyCam easyCam;

        float camDist;
};
