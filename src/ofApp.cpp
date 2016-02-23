#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  for( int i=1; i<arguments.size(); i++ ) {
    Architecture temp(arguments.at(i));
    images.push_back(temp);
  }
}

void ofApp::update() {};

void ofApp::draw() {
  if(arguments.size() > 0) {
    images.at(toDisplay).drawImage();
  } else {
    exit();
  }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {
  if(toDisplay < images.size()-1) {
    toDisplay ++;
  } else {
    toDisplay = 0;
  }
}
