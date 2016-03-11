#include "ofMain.h"
#include "ofApp.h"

int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
