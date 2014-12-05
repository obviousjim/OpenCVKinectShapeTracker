#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"

class ShapeDetector
{
  public:
	void setup();
	void update();
	void draw();

	ofxKinectCommonBridge kinect;
	ofImage mappedColor;
};
