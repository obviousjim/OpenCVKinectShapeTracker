#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"
#include "ofxCv.h"
#include "ofxUI.h"
#include "ofxImageSegmentation.h"

//#define SHAPE_COLOR_COUNT 8
//typedef int ShapeColor;

//TODO 
//-- add filters
//	-- small contours
//	-- large contours
//	-- uncompact contours
//-- show only valid contours
//-- iterate through the contours
//-- show stats of contours

//-- add instructions to interface

//OPTIMIZATIONS
//-- optimize kinect
//-- optimize image segmenter

class ShapeContour {
  public:
	ShapeContour(){
		valid = false;
		contourArea = 0;
		circleRadius = 0;
		rectMaxSide = 0;
		compactness = false;
		depthPosition = false;
	}

	bool valid;
	ofPolyline contour;	
	ofImage segmentedDepthImage;
	ofImage segmentedColorImage;

	cv::Rect boundingRect;
	cv::RotatedRect fitEllipse;
	cv::RotatedRect fitRect;
	float contourArea;
	
	ofVec2f circlePosition;
	float circleRadius;
	float rectMaxSide;

	float compactness;
	float depthPosition;
};

class ShapeDetector
{
  public:
	void setup();
	void update();
	void draw();
	void exit();

	void mouseMoved(ofMouseEventArgs& args);
	void mouseDragged(ofMouseEventArgs& args);
	void mousePressed(ofMouseEventArgs& args);
	void mouseReleased(ofMouseEventArgs& args);

	void keyPressed(ofKeyEventArgs& args);
	void keyReleased(ofKeyEventArgs& args);

	void findShapes();

  protected:

	vector<ShapeContour> contours;
	ofxKinectCommonBridge kinect;
	ofxImageSegmentation imageSegmentation;

	ofImage depthColors;
	ofImage segmentedDepthColors;

	ofFbo zoomFbo;
	ofVec2f zoomPoint;

	int depthImageWidth;
	int depthImageHeight;

	void drawDebug(bool zoom);
	void drawContour(ShapeContour& contour, bool showStats);

	//updates the current list of contours based on any changes to the filter settings
	void revalidateContours();

	ofxUISuperCanvas* gui;
	float minArea;
	float maxArea;
	float minCompactness;

	//previewing contours one at a time
	vector<int> validContours;
	int currentSelectedContour;

	//visualization parameters
	bool showAllContours;
	bool previewEllipseFit;
	bool previewRectFit;
	bool previewCircleFit;
	bool previewStats;

	//void createDepthMasks();
	string getSettingsFilename();
};
