#include "ofApp.h"
using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofAddListener(ofEvents.keyPressed, this, &ofApp::updatePictures)
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Sensitive);
    
    cam.setup(w,h);
    
    fbo.allocate(w,h);
    fbo.allocate(ofGetWidth(),ofGetHeight(),GL_LUMINANCE);

}

//--------------------------------------------------------------
void ofApp::update() {
    cam.update();
    if( cam.isFrameNew() ) {
        // finder.update(cam);
    }
}



//--------------------------------------------------------------
void ofApp::draw() {
    fbo.begin();
    ofClear(255,255,255, 0);
    ofSetColor(255,255,255);
    ofPushStyle();
    ofFill();
    for(int i = 0; i < finder.size(); i++) {
        ofBeginShape();
        ofRectangle object = finder.getObjectSmoothed(i);
        ofDrawRectangle(object);
        ofEndShape(true);
    }
    ofPopStyle();
    fbo.end();
    cam.draw(0,0);
    cam.getTexture().setAlphaMask(fbo.getTexture());
}

//--------------------------------------------------------------
// update the app 
void ofApp::updatePictures(int key){
ofLog(OF_LOG_NOTICE, "the number is " + ofToString(key));
}




