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

class Segment {
  private:
    static int count; // Global count of objects createdd

    const int cCount; // local cache of global segment count
    const ofPoint topLeft; // location of the segment in the original image
    ofImage imgSeg; // the image data in ofImage format
    ofImage imgSegH; // ditto ^ but for hough lines

    void removeBackground();
    bool exportSegments();

  public:
    Segment(ofImage _imgSegH, ofImage _imgSeg, ofPoint _topLeft);
    void exportSegment();
    bool pixelDif(int r1, int g1, int b1, int r2, int g2, int b2);
};
