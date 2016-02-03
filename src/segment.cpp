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

Segment::Segment(ofImage _imgSegH, ofImage _imgSeg, ofPoint _topLeft): imgSegH(_imgSegH), imgSeg(_imgSeg), topLeft(_topLeft), cCount(count++) {}

int Segment::count = 0;

void Segment::exportSegment() {
  removeBackground();
  string name = "seg/segment" + to_string(cCount) + ".png";
  
  imgSeg.save(name, OF_IMAGE_QUALITY_BEST);
}

void Segment::removeBackground() {
  int w = imgSeg.getWidth();
  int h = imgSeg.getHeight();
  int dim = w * h;

  int yVal; // stores the y val of the hough line intersection found

  unsigned char * pix = imgSeg.getPixels(); // Pointer to the start of the pixel buffer for output img
  unsigned char * houghPix = imgSegH.getPixels(); // Pointer to the start of the pixel buffer for pic with hough lines

  for( int i=0; i<dim; i++ ) {
    int loc = i * 3;

    int r = houghPix[loc];
    int g = houghPix[loc+1];
    int b = houghPix[loc+2];

    /*
     * DETECT VERTICAL HOUGH LINE
     * Check values 2 pixels back and forward
     *
     * loc > 1 - Ensure we aren't getting out of bounds of pointer
     * r >= 230 - If pixel intersects red hough line
     * pixelDif() - If pixel before and after it are adaquately different
     * loc < dim*3-2 - Ensure we aren't getting out of upper bounds of pointer
     */
      if (loc > 3 && r >= 230 && pixelDif(pix[loc-4], pix[loc+8]) && loc < dim*3-2)
        yVal = i / w;

      // Catch the remaining pixels after a genuine HL intersection, on the same line
      if (yVal == i / w) {
        pix[loc] = 255;
        pix[loc+1] = 255;
        pix[loc+2] = 255;
      }
  }

  imgSeg.update();
}

bool Segment::pixelDif(int pix1, int pix2) {
  return abs(pix1 - pix2) > 75;
}
