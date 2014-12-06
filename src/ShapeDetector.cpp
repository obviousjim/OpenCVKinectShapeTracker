#include "ShapeDetector.h"

//--------------------------------------------------------------
void ShapeDetector::setup(){

	//Initialize the sensors with a depth and color image channel
	kinect.initSensor();
	kinect.initDepthStream(true);
	kinect.initColorStream();
	kinect.start();

	depthImageWidth  = kinect.getDepthPixelsRef().getWidth(); 
	depthImageHeight = kinect.getDepthPixelsRef().getHeight();

	depthColors.allocate(depthImageWidth,depthImageHeight,OF_IMAGE_COLOR);

	background.allocate(		depthImageWidth, depthImageHeight , OF_IMAGE_GRAYSCALE);
	thresholdedScene.allocate(	depthImageWidth, depthImageHeight , OF_IMAGE_GRAYSCALE);
	scanScene.allocate(			depthImageWidth, depthImageHeight , OF_IMAGE_GRAYSCALE);
	contourPix.allocate(		depthImageWidth, depthImageHeight , OF_IMAGE_GRAYSCALE);
	depthColors.allocate(		depthImageWidth, depthImageHeight , OF_IMAGE_COLOR);

	for(int i = 0; i < SHAPE_COLOR_COUNT; i++){
		colorMasks[(ShapeColor)i].allocate(depthImageWidth, depthImageHeight, OF_IMAGE_GRAYSCALE);
		maskedDepthColors[(ShapeColor)i].allocate(depthImageWidth, depthImageHeight, OF_IMAGE_COLOR);
		colorDepthCompositeMask[(ShapeColor)i].allocate(depthImageWidth, depthImageHeight, OF_IMAGE_GRAYSCALE);
	}

	gui = new ofxUISuperCanvas("SHAPEGUI", 200,0,200,700);
	gui->addRangeSlider("DEPTH RANGE",500,900,&minScanDistance,&maxScanDistance);
	gui->addSlider("MIN AREA", 0, 100, &minArea);
	gui->addSlider("SHIFT X", -10, 10, &shift.x);
	gui->addSlider("SHIFT Y", -10, 10, &shift.y);
	gui->addSpacer();
	gui->addToggle("PREVIEW ELLIPSE",&previewEllipseFit);
	gui->addToggle("PREVIEW RECT",&previewRectFit);
	gui->addToggle("PREVIEW CIRCLE", &previewCircleFit);
	gui->addToggle("PREVIEW STATS", &previewStats);

	for(int i = 0; i < SHAPE_COLOR_COUNT; i++){
		sampleConnectors[i] = false;
	}

	gui->loadSettings(getSettingsFilename());

	loadColors();
}

//--------------------------------------------------------------
void ShapeDetector::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		kinect.mapDepthToColor(depthColors.getPixelsRef());
		depthColors.update();
	}
}

//--------------------------------------------------------------
void ShapeDetector::draw(){
	depthColors.draw(0,0);
}

void ShapeDetector::createColorMasks(){
	for(int i = 0; i < SHAPE_COLOR_COUNT; i++){
		ShapeColor colorIndex = (ShapeColor)i;
		createColorMask(colorIndex);
	}	
}

void ShapeDetector::createColorMask(ShapeColor colorIndex){
	
	cv::Mat img = ofxCv::toCv(depthColors);
	cv::Mat threshold = ofxCv::toCv(colorMasks[colorIndex]);
	cv::Mat masked = ofxCv::toCv(maskedDepthColors[colorIndex]);

	ofColor targetColor = colorSamples[colorIndex][0].color;
	cv::Scalar offset(colorSamples[colorIndex][0].hueRange, 
					  colorSamples[colorIndex][0].saturationRange, 
					  colorSamples[colorIndex][0].valueRange);

	cv::cvtColor(img, hsvImage, CV_RGB2HSV);
	cv::Scalar base = ofxCv::toCv(ofxCv::convertColor(targetColor, CV_RGB2HSV));
	cv::Scalar lowerb = base - offset;
	cv::Scalar upperb = base + offset;
	cv::inRange(hsvImage, lowerb, upperb, tempThresh);
	
	masked.setTo(0);
	img.copyTo(masked,tempThresh);

	targetColor = colorSamples[colorIndex][1].color;
	offset = cv::Scalar(colorSamples[colorIndex][1].hueRange, 
						colorSamples[colorIndex][1].saturationRange, 
					    colorSamples[colorIndex][1].valueRange);

	cv::cvtColor(img, hsvImage, CV_RGB2HSV);
	base = ofxCv::toCv(ofxCv::convertColor(targetColor, CV_RGB2HSV));
	lowerb = base - offset;
	upperb = base + offset;
	cv::inRange(hsvImage, lowerb, upperb, threshold);

	img.copyTo(masked,threshold);
	cv::add( threshold, tempThresh, threshold );

	colorMasks[colorIndex].update();
	maskedDepthColors[colorIndex].update();
	
}

void ShapeDetector::exit(){
	saveColors();
	gui->saveSettings(getSettingsFilename());
}


void ShapeDetector::saveColors(){
	ofBuffer colorBuffer;

	for(int s = 0; s < 2; s++){
		for(int i = 0; i < SHAPE_COLOR_COUNT; i++){
			colorBuffer.append( ofToString( (int) colorSamples[(ShapeColor)i][s].color.r) + "," +
								ofToString( (int) colorSamples[(ShapeColor)i][s].color.g) + "," +
								ofToString( (int) colorSamples[(ShapeColor)i][s].color.b) + "," +
								ofToString( (int) colorSamples[(ShapeColor)i][s].hueRange) + "," +
								ofToString( (int) colorSamples[(ShapeColor)i][s].saturationRange) + "," +
								ofToString( (int) colorSamples[(ShapeColor)i][s].valueRange) + "\n");
		}
	}
	ofBufferToFile(getColorFilename(),colorBuffer);
}

void ShapeDetector::loadColors(){

	if(!ofFile(getColorFilename()).exists()){
		return;
	}

	ofBuffer colorBuffer = ofBufferFromFile(getColorFilename());
	int index = 0;
	while(!colorBuffer.isLastLine()){
		string line = colorBuffer.getNextLine();
		vector<string> colorComponents = ofSplitString(line,",",true,true);
		ShapeColor i = (ShapeColor )(index % SHAPE_COLOR_COUNT);
		int s = index/SHAPE_COLOR_COUNT;
		colorSamples[i][s].color = 
			ofColor(ofToInt(colorComponents[0]),
					ofToInt(colorComponents[1]),
					ofToInt(colorComponents[2]));

		if(colorComponents.size() > 3){
			colorSamples[i][s].hueRange			= ofToInt(colorComponents[3]);
			colorSamples[i][s].saturationRange	= ofToInt(colorComponents[4]);
			colorSamples[i][s].valueRange		= ofToInt(colorComponents[5]);
		}
		else{
			colorSamples[i][s].hueRange			= 0;
			colorSamples[i][s].saturationRange	= 0;
			colorSamples[i][s].valueRange		= 0;
		}
		index++;
	}
}

string ShapeDetector::getSettingsFilename(){
	return "settings/settings.xml";
}

string ShapeDetector::getColorFilename(){
	return "settings/colors.xml";	
}

string ShapeDetector::getColorRangeFilename(){
	return "settings/colorranges.xml";	
}

