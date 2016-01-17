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
  float tVal;

  ofxCv::ContourFinder contourFinder;
  ofxCv::TrackingColorMode tcm;
  ofColor targetColor;
};
