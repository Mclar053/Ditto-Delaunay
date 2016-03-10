/**
 * segment.h
 *
 * Describes a subsection of an image and provides
 * an interface to export them.
 *
 * @author James Oldfield
 * @version 1.0 25/01/16
 */

#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class Segment {
  private:
    static int segCount; // Global count of objects created

    const int cCount; // local cache of global segment count
    const ofPoint topLeft; // location of the segment in the original image
    ofImage imgSeg; // the image data in ofImage format
    ofImage imgSegH; // ditto ^ but for hough lines
    vector<ofPoint> edges; // stores the location of segment edges
    int h, w; // image width and height
    int imageNo; // Image index, used for folder number.

    ofxCv::ContourFinder contourFinder;

    void removeBackground();
    bool exportSegments();

  public:
    Segment(ofImage _imgSegH, ofImage _imgSeg, ofPoint _topLeft, int _imageNo);
    void exportSegment();
    void addVertex(int i, int row); // Declare a pixel a vertex of the shape
};
