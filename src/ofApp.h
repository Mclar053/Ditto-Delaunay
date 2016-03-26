#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxDelaunay.h"
#include "architecture.h"
#include "triangle-seg.hpp"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);

    ofxDelaunay triangulation;
    vector<Tri_Segment> segs;
    
    ofTrueTypeFont* font;
};
