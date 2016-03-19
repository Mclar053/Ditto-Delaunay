#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  Architecture img = Architecture("http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006");
  Architecture img2 = Architecture("long.jpg");

  images.push_back(img);
  images.push_back(img2);
}

void ofApp::update() {};

void ofApp::draw() {
  images.at(toDisplay).drawImage();
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {
  if(toDisplay < images.size()-1) {
    toDisplay ++;
  } else {
    toDisplay = 0;
  }
}
