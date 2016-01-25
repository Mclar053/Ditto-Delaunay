#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void mousePressed(int x, int y, int button);
  void keyPressed(int key);
  
  ofImage image;
  ofImage thresh;

  vector<ofPolyline> cartCoord; // Storing the cartesian representations of lines
  vector<ofPoint> iPts;

  bool doSegsIntersect(ofPolyline a, ofPolyline b);
};
