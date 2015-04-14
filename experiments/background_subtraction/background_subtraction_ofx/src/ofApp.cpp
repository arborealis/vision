#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetFrameRate(240);
	ofSetVerticalSync(true);
    
	cam.initGrabber(1280, 720);

//	 imitate() will set up previous and diff
//	 so they have the same size and type as cam
	imitate(previous, cam);
	imitate(diff, cam);
    
    start_time = ofGetSystemTimeMicros();
    count = 0;
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		// take the absolute difference of prev and cam and save it inside diff
		absdiff(previous, cam, diff);
		diff.update();
		copy(cam, previous);
        
        count++;
        
        if (ofGetSystemTimeMicros() - start_time > 5000000) {
            double fps = (float) count / (ofGetSystemTimeMicros() - start_time) * 1000000;
            printf("Effective framerate: %.1ffps\n", fps);
            count = 0;
            start_time = ofGetSystemTimeMicros();
        }
	}
}

void ofApp::draw() {
	ofSetColor(255);
	diff.draw(0, 0);
}
