#include "ofApp.h"
#include "SweepLine.h"
#include "main.h"
#include "bintree.h"

using namespace ofxCv;
using namespace cv;

vector<Vec2f> lines; // Storing the Hough lines
vector<ofPolyline> cartCoord; // Storing the cartesian representations of lines
Mat threshBin, img; // cv-style binary image

static set<PointSL*> outpoints;
vector<SLseg*> segmenty;

// Functionality to compute the segments
class SweepLine;
void get_intersections( vector<SLseg*> segmenty, set<PointSL*> *outp) {
  EventQueue  Eq(segmenty);
  SweepLine  *SL = new SweepLine();
  Event      *e;  /* current event */
  SLseg      *s;  /* current segment sweepline-u */

  /* go through all events, it's either lavy top, right top or intersection */
  while (e = Eq.next()) {
    switch (e->type) {
      case LEFT:
        {
          /* add to sweep-lines */
          s = SL->add(e);
          if (s) {
            if (s->above) {
              SL->intersect(s->above, s, &Eq);
            }

            if (s->below) {
              SL->intersect(s, s->below, &Eq);
            }
          }
          break;
        }
      case RIGHT:
        {
          /* taken from sweep-lines */
          s = SL->find(e);
          if (s) {
            SLseg *tempa;
            SLseg *tempb;
            tempa = s->above;
            tempb = s->below;
            SL->remove(s);
            if (tempa && tempb) {
              SL->intersect(tempa, tempb, &Eq);
            }
          }
          break;
        }
      case INTERSECTION:
        {
          outp->insert(e->eV);

          /* the point where it therefore to one another upper and lower */
          SLseg *tmp = e->intersectUpper->above;
          e->intersectUpper->above = e->intersectLower;
          e->intersectLower->above = tmp;
          e->intersectUpper->below = e->intersectLower->below;
          e->intersectLower->below = e->intersectUpper;
          tmp = NULL;

          /* to rearrange the segments adjacent to the intersection */
          SL->intersect(e->intersectLower->above, e->intersectLower, &Eq);
          SL->intersect(e->intersectUpper->below, e->intersectUpper, &Eq);
          break;
        }
    }
  }
}

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

  segmenty.clear();
  outpoints.clear();

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

     segmenty.push_back(new SLseg( new PointSL(pt1.x, pt1.y), new PointSL(pt2.x, pt2.y)));
     cartCoord.push_back(tmp);
  }

  // compute the intersection Hough Lines
  get_intersections(segmenty, &outpoints);
}

void ofApp::update() {
  image.update();
}

void ofApp::draw() {
  image.draw(0, 0);
  for(auto line : cartCoord) {
    ofColor(255);
    ofFill();
    line.draw();
  }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {}
