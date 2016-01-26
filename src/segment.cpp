/**
 * segment.cpp
 *
 * Describes a subsection of an image and provides
 * an interface to export them.
 *
 * @author James Oldfield
 * @version 1.0 25/01/16
 */

#include "segment.h"

Segment::Segment(ofImage imgData): imgSeg(imgData), cCount(count++) {}

int Segment::count = 0;

void Segment::exportSegment() {
  string name = "seg/segment" + to_string(cCount) + ".png";
  
  imgSeg.save(name, OF_IMAGE_QUALITY_BEST);
}
