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
    static int count;

    bool exportSegments();
    const int cCount;
    ofImage imgSeg;

  public:
    Segment(ofImage imgData);
    void exportSegment();
};
