#pragma once

#include "ofMain.h"
#include "ShapeDetector.h"
#include "ofxKinectCommonBridge.h"
#include "ofxCv.h"
#include "ofxUI.h"

struct CurioContour {
	
	//FROM SCAN
	float depthRangeMin;
	float depthRangeMax;
	ofPolyline contour;
	
	//FROM CV
	bool valid;
	cv::Rect boundingRect;
	cv::RotatedRect fitEllipse;
	cv::RotatedRect fitRect;
	
	ofVec2f circlePosition;
	float circleRadius;
	float rectMaxSide;
	
	//COMPUTED
	float depthPosition; //depth of sensed position
	float coordRadius; //radius of sense cross section
};

enum ShapeColor {

	COLOR_SPHERE_LIGHTGREEN = 0,
	COLOR_SPHERE_BLUE,
	COLOR_SPHERE_MAROON,
		
	COLOR_CUBE_LAVENDER,
	COLOR_CUBE_RED,
	COLOR_CUBE_SALMON,

	COLOR_CONNECTOR_CYAN,
	COLOR_CONNECTOR_GREEN,
	COLOR_CONNECTOR_PURPLE,
	COLOR_CONNECTOR_ORANGE,
	COLOR_CONNECTOR_FUSCHIA,
	COLOR_CONNECTOR_YELLOW,

	SHAPE_COLOR_COUNT
};


//color selection and layer tracking
//-- add color picker
//-- add color layers 
//-- add debug view
//-- add 3D view
//-- make kinect mapping faster

struct CurioColorSlider {
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

	bool sampleConnectors[SHAPE_COLOR_COUNT];
	int sampleColorIndex;

	void saveColors();
	void loadColors();

	void createColorMask(ShapeColor colorIndex);
	void createColorMasks();

	ofImage depthColors;
	ofShortImage background;
	ofShortImage scanScene;
	ofShortImage thresholdedScene;
	ofPixels contourPix;

	map<ShapeColor, vector<CurioColorSlider> > colorSamples;
	map<ShapeColor, ofImage> colorMasks;
	map<ShapeColor, ofImage> maskedDepthColors;
	map<ShapeColor, ofFloatImage> colorDepthCompositeMask;

	string getSettingsFilename();
	string getColorFilename();
	string getColorRangeFilename();

	cv::Mat hsvImage;
	cv::Mat tempThresh;
};
