#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  for( int i=2; i<arguments.size(); i++ ) {
    // Pass each image and the threshold
    Architecture temp(arguments.at(i), stoi(arguments.at(1)));
    images.push_back(temp);
  }

  Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
}

void ofApp::update() {};

void ofApp::draw() {
  if(arguments.size() > 0) {
    images.at(toDisplay).drawImage();
  } else {
    exit();
    cout << "No images supplied, or incorrectly... exiting." << endl;
  }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_RETURN) {
    // Loop through the pictures
    if (toDisplay < images.size()-1)
      toDisplay ++;
  else
    toDisplay = 0;
  } else if (key == OF_KEY_RIGHT) {
    // Loop through the segments to compare.
    if (toCompare.x < images.at(0).segments.size()-1)
      toCompare.x ++;
    else
      toCompare.x = 0;

    if (toCompare.y < images.at(1).segments.size()-1)
      toCompare.y ++;
    else
      toCompare.y = 0;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  } else if (key == OF_KEY_LEFT) {
    // Loop through the segments to compare.
    if (toCompare.x > 0)
      toCompare.x --;
    else
      toCompare.x = images.at(0).segments.size()-1;

    if (toCompare.y > 0)
      toCompare.y --;
    else
      toCompare.y = images.at(1).segments.size()-1;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  }
}
