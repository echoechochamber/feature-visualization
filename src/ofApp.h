#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include <cvVisualizer.hpp>

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    int stage_to_draw = 0;
    
    int w = 1280;
    int h = 720;
    ofPath path;
    ofVideoGrabber cam;
    
    ofFbo fbo;
    ofxCv::ObjectFinder finder;
    CvVisualizer cv;
};
