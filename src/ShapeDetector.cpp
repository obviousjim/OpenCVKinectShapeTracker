#include "ShapeDetector.h"

//--------------------------------------------------------------
void ShapeDetector::setup(){

	kinect.initSensor();
	kinect.initDepthStream(true);
	kinect.initColorStream();
	kinect.start();

	int width  = kinect.getDepthPixelsRef().getWidth(); 
	int height = kinect.getDepthPixelsRef().getHeight();

	mappedColor.allocate(width,height, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ShapeDetector::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		kinect.mapDepthToColor(mappedColor.getPixelsRef());
		mappedColor.update();
	}
}

//--------------------------------------------------------------
void ShapeDetector::draw(){
	//kinect.draw(0,0);
	mappedColor.draw(0,0);
}
