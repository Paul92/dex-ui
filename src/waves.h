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

        void setPosition(ofPoint p);

        void update();
        void draw();

        int getUpdatePosition();

        int sign(float x);
        void drawCorner(ofPoint p);

        float freezet;
        float old_zh, new_zh;
        float w, h;
        float zh;
        float noise_scale;

        float rotateX;
        float rotateY;
        float rotateZ;

        float rotateZ_rate;
        float update_sweep_rate;

        ofMesh mesh;
        ofPlanePrimitive plane;
        ofShader waveShader;
        ofShader outlineShader;
        ofImage displacementTexture;
        int texw, texh;

        ofEasyCam easyCam;

        float camDist;
        ofPoint view;
};
