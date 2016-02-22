#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "architecture.h"

class ofApp : public ofBaseApp {
public:
  void setup();
  void update();
  void draw();
  void mousePressed(int x, int y, int button);
  void keyPressed(int key);

  vector<Architecture> images;
};
