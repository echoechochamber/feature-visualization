#include "ofApp.h"
using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    cv.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Sensitive);
    
    cam.setup(w,h);
    
    fbo.allocate(w,h);
    fbo.allocate(ofGetWidth(),ofGetHeight(),GL_LUMINANCE);
}

//--------------------------------------------------------------
void ofApp::update() {
    cam.update();
    if( cam.isFrameNew() ) {
//        finder.update(cam);
    }
}



//--------------------------------------------------------------
void ofApp::draw() {

//    cv.draw();
    cv.drawStage(stage_to_draw);
}

//--------------------------------------------------------------


void ofApp::keyPressed(int key){
    if(key == OF_KEY_LEFT){
        if(stage_to_draw > 0 ){
            stage_to_draw = stage_to_draw - 1;
        }
    }else if(key == OF_KEY_RIGHT){
        if(stage_to_draw < cv.numStages() - 1){
            stage_to_draw = stage_to_draw + 1; 
        }
    }
}


