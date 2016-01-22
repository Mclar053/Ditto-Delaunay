#include "ofApp.h"
#include "ofxIntersection.h"

using namespace ofxCv;
using namespace cv;

vector<Vec2f> lines; // Storing the Hough lines
vector<IsLine> cartCoord; // Storing the cartesian representations of lines
Mat threshBin, img; // cv-style binary image

void ofApp::setup() {
  // image.loadImage("http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006");
  image.loadImage("http://static.dezeen.com/uploads/2008/02/squareparabola03.jpg");

  thresh.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  convertColor(image, thresh, CV_RGB2GRAY);
  
  // Apply the canny edge detector for better segmentation
  Canny(image, thresh, 50, 200, 3);
  thresh.update();

  // Map the OF image data to a cv-style binary data
  threshBin = toCv(thresh);

  // Apply the Hough Lines transform
  HoughLines(threshBin, lines, 1, CV_PI/180, 125, 0, 0);

  img = toCv(image); // Convert OF image to CV bin representation

  for( int i = 0; i < lines.size(); i++ ) {
     float rho = lines[i][0], theta = lines[i][1];
     cv::Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 1000*(-b));
     pt1.y = cvRound(y0 + 1000*(a));
     pt2.x = cvRound(x0 - 1000*(-b));
     pt2.y = cvRound(y0 - 1000*(a));
     line( img, pt1, pt2, Scalar(255,0,0), 1, CV_AA);

     // Cache the cartesian representations in vector storage
     IsLine cartLine(ofPoint(pt1.x, pt1.y, 0), ofPoint(pt2.x, pt2.y, 0));
     cartCoord.push_back(cartLine);

     cout << cartCoord[i].getVec() << endl;
  }
}

void ofApp::update() {
  image.update();
}

void ofApp::draw() {
  image.draw(0, 0);
  for(auto line : cartCoord) {
    line.draw();
  }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
