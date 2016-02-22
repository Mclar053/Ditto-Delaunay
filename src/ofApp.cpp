#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  Architecture img = Architecture("http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006");

  images.push_back(img);
}

void ofApp::update() {};

void ofApp::draw() {
  images.at(0).drawImage();
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
