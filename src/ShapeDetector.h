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

struct ShapeContour {
	
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

	void findShapes();

  protected:

	vector<ShapeContour> contours;
	int currentSelectedContour;
	ofxKinectCommonBridge kinect;
	ofxImageSegmentation imageSegmentation;

	void drawDebug(bool zoom);
	int depthImageWidth;
	int depthImageHeight;

	ofxUISuperCanvas* gui;
	float minArea;
	float maxArea;

	//visualization parameters
	bool showAllContours;
	bool previewEllipseFit;
	bool previewRectFit;
	bool previewCircleFit;
	bool previewStats;

	void createDepthMasks();

	ofImage depthColors;
	ofImage segmentedDepthColors;

	ofFbo zoomFbo;
	ofVec2f zoomPoint;

	string getSettingsFilename();
};
