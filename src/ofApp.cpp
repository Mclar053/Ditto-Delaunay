#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  Architecture img = Architecture("http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006");
  Architecture img2 = Architecture("long.jpg");

  images.push_back(img);
  images.push_back(img2);

  Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
}

void ofApp::update() {};

void ofApp::draw() {
  images.at(toDisplay).drawImage();
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
