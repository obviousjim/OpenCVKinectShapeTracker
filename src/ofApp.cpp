#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0);

	detector.setup();

	ofRegisterMouseEvents(&detector);
	ofRegisterKeyEvents(&detector);

}

//--------------------------------------------------------------
void ofApp::update(){
	detector.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	detector.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == ' '){
		detector.findShapes();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit(){
	ofUnregisterMouseEvents(&detector);
	ofUnregisterKeyEvents(&detector);
	detector.exit();
}

