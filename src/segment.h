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

    bool exportSegments();
    const int cCount; // local cache of global segment count
    ofImage imgSeg; // the image data in ofImage format
    ofPoint topLeft; // location of the segment in the original image

  public:
    Segment(ofImage _imgSeg, ofPoint _topLeft);
    void exportSegment();
};
