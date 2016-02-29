#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  for( int i=2; i<arguments.size(); i++ ) {
    // Pass each image and the threshold
    Architecture temp(arguments.at(i), stoi(arguments.at(1)));
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
