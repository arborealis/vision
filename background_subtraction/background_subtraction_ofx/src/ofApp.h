#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include <opencv/highgui.h>  
#include <opencv2/core/core.hpp>  

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ofPixels previous;
	ofImage diff;
    unsigned long long start_time;
    int count;
	
	// a scalar is like an ofVec4f but normally used for storing color information
	cv::Scalar diffMean;
};
