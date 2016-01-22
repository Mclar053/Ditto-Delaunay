#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

vector<Vec2f> lines; // Storing the Hough lines
vector<ofPolyline> cartCoord; // Storing the cartesian representations of lines
vector<ofPoint> iPts; // Stores the points of intersection with Hough Lines
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
     ofPolyline tmp;

     tmp.addVertex( ofPoint(pt1.x, pt1.y, 0) );
     tmp.addVertex( ofPoint(pt2.x, pt2.y, 0) );
     tmp.close();

     cartCoord.push_back(tmp);
  }

  // Check for line intersection via brute force
  for(auto l1 : cartCoord) {
    for(auto l2 : cartCoord) {
      doSegsIntersect(l1, l2);
    }
  }

}

void ofApp::update() {
  image.update();
}

void ofApp::draw() {
  image.draw(0, 0);
  // for(auto line : cartCoord) {
  //   ofColor(255);
  //   ofFill();
  //   line.draw();
  // }
  for(auto pt : iPts) {
    ofCircle(pt.x, pt.y, 2);
  }
}

bool ofApp::doSegsIntersect(ofPolyline a, ofPolyline b) {
  /*
   * Function loosely based on answers from: http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
   */
  vector<ofPoint> aLine = a.getVertices();
  vector<ofPoint> bLine = b.getVertices();

  float a0x = aLine[0].x;
  float a0y = aLine[0].y;
  float a1x = aLine[1].x;
  float a1y = aLine[1].y;

  float b0x = bLine[0].x;
  float b0y = bLine[0].y;
  float b1x = bLine[1].x;
  float b1y = bLine[1].y;

  float s1x = a1x - a0x;
  float s1y = a1y - a0y;
  float s2x = b1x - b0x;
  float s2y = b1y - b0y;

  float s, t;
  s = (-s1y * (a0x - b0x) + s1x * (a0y - b0y)) / (-s2x * s1y + s1x * s2y);
  t = ( s2x * (a0y - b0y) - s2y * (a0x - b0x)) / (-s2x * s1y + s1x * s2y);

  // If a collision has been detected
  if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
    iPts.push_back( ofPoint(a0x + (t * s1x), a0y + (t * s1y)) );
    return 1;
  }

  return 0; // No collision

}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
