#include "ofApp.h"
#include <math.h>

using namespace ofxCv;
using namespace cv;

vector<Vec4i> lines; // Storing the Hough lines
Mat threshBin, img; // cv-style binary image

void ofApp::setup() {
  image.loadImage("image.jpg");

  thresh.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  convertColor(image, thresh, CV_RGB2GRAY);
  
  // Apply the canny edge detector for better segmentation
  Canny(image, thresh, 50, 200, 3);
  thresh.update();

  // Map the OF image data to a cv-style binary data
  threshBin = toCv(thresh);

  // Apply the Hough Lines transform
  HoughLinesP(threshBin, lines, 1, CV_PI/180, 50, 50, 10);

  img = toCv(image); // Convert OF image to CV bin representation

  for( size_t i = 0; i < lines.size(); i++ ) {
    Vec4i l = lines[i];
    cv::line( img, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
  }

}

void ofApp::update() {}

void ofApp::draw() {

  image.update();
  image.draw(0, 0);
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
