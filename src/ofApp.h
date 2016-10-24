#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include <cvVisualizer.hpp>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void updatePictures(int key); // change the value of the
    
        int w = 1280;
        int h = 720;
        ofPath path;
        ofVideoGrabber cam;
        
        ofFbo fbo;
        ofxCv::ObjectFinder finder;
        CvVisualizer cv;
};
