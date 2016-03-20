/**
 * architecture.h
 *
 * Describes a representation of an input image
 *
 * @author James Oldfield
 * @version 1.0 22/02/16
 */

#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "segment.h"

using namespace ofxCv;
using namespace cv;

class Architecture {
  private:
    static int arcCount; // Global count of objects created

    const int cCount; // local cache of global architecture count
    ofImage image;
    ofImage thresh;

    vector<ofPolyline> cartCoord; // Storing the cartesian representations of lines
    vector<ofPoint> iPts;

    vector<Vec2f> lines; // Storing the Hough lines
    Mat threshBin, img; // cv-style binary image
    ofImage imgCopy; // copy of the imange without the Hough Lines

    bool doSegsIntersect(ofPolyline a, ofPolyline b);

  public:
    Architecture(string _image);
    void drawImage();

    vector<Segment> segments;
};
