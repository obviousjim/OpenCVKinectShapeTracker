#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"
#include "ofxCv.h"
#include "ofxUI.h"
#include "ofxImageSegmentation.h"

//TODO 
//-- add filters
//	-- uncompact contours
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
	ofShortImage segmentedDepthImage;
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
	int depthImageWidth;
	int depthImageHeight;

	//updates the current list of contours based on any changes to the filter settings
	void revalidateContours();
	//previewing contours one at a time
	vector<int> validContours;
	int currentSelectedContour;

	ofImage currentColorFrame;   //current color image from the Kinect mapped to depth
	ofImage segmentedColorFrame; //captured color image the segmentation was run on
	ofImage segmentationKey;	 //colorized segmentation image

	void drawDebug(bool zoom);
	void drawContour(ShapeContour& contour, bool showStats);
	ofFbo zoomFbo;
	ofVec2f zoomPoint;

	ofxUISuperCanvas* gui;
	//filters
	float minArea;
	float maxArea;
	float minCompactness;

	//visualization parameters
	bool showAllContours;
	bool showSegmentationKey;
	bool previewEllipseFit;
	bool previewRectFit;
	bool previewCircleFit;
	bool previewStats;

	string getSettingsFilename();
};
