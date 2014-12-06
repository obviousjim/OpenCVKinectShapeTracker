#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"
#include "ofxCv.h"
#include "ofxUI.h"

#define SHAPE_COLOR_COUNT 8
typedef int ShapeColor;

struct ShapeContour {
	
	//FROM SCAN
	ofPolyline contour;
	
	//FROM CV
	cv::Rect boundingRect;
	cv::RotatedRect fitEllipse;
	cv::RotatedRect fitRect;
	
	ofVec2f circlePosition;
	float circleRadius;
	float rectMaxSide;
	
	//COMPUTED
	float depthPosition; //depth of sensed position
	float coordRadius; //radius of sense cross section

	//shape info
	ShapeColor color;
	float contourArea;
};

class ColorSlider {
  public:
	ColorSlider(){
		hueRange = 0;
		saturationRange = 0;
		valueRange = 0;
	};

	ofRectangle samplePos;
	ofRectangle hpos;
	ofRectangle spos;
	ofRectangle vpos;
	ofColor color;
	int hueRange;
	int saturationRange;
	int valueRange;
};

class ShapeDetector
{
  public:
	void setup();
	void update();
	void draw();
	void exit();

  protected:

	void drawDebug(bool zoom);

	ofxKinectCommonBridge kinect;
	int depthImageWidth;
	int depthImageHeight;

	ofxUISuperCanvas* gui;
	//scanning parameters
	ofVec2f shift;
	float minScanDistance;
	float maxScanDistance;
	float minArea;

	//visualization parameters
	bool showAllContours;
	bool previewColors;
	bool previewEllipseFit;
	bool previewRectFit;
	bool previewCircleFit;
	bool previewStats;

	int sampleColorIndex;

	void saveColors();
	void loadColors();

	void createColorMask(ShapeColor colorIndex);
	void createColorMasks();
	void findShapes();

	cv::Mat hsvImage;
	cv::Mat tempThresh;
	ofImage depthColors;
	ofShortImage background;
	ofShortImage scanScene;
	ofShortImage thresholdedScene;
	ofPixels contourPix;

	ofFbo zoomFbo;
	ofVec2f zoomPoint;

	vector<bool>sampleConnectors;
	vector< vector<ColorSlider> > colorSamples;
	vector<ofImage> colorMasks;
	vector<ofImage> maskedDepthColors;
	vector<ofFloatImage> colorDepthCompositeMask;
	vector<ShapeContour> contours;
	vector<ColorSlider> colorSliders;

	string getSettingsFilename();
	string getColorFilename();
	string getColorRangeFilename();


};
