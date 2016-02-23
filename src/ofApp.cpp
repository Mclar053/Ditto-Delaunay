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
  images.at(0).drawImage();
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
