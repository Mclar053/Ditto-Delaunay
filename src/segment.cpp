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
  string name = "seg/segment" + to_string(cCount) + "-new.png";
  string houghName = "seg/segment" + to_string(cCount) + "-hough.png";
  
  imgSeg.save(name, OF_IMAGE_QUALITY_BEST);
  imgSegH.save(houghName, OF_IMAGE_QUALITY_BEST);
}

void Segment::removeBackground() {
  int w = imgSeg.getWidth();
  int h = imgSeg.getHeight();
  int dim = w * h;

  int yValDelete; // stores the y val of the hough line intersection found
  int yValIgnore; // stores the y val of a found horizontal hough line to ignore

  unsigned char * pix = imgSeg.getPixels(); // Pointer to the start of the pixel buffer for output img
  unsigned char * houghPix = imgSegH.getPixels(); // Pointer to the start of the pixel buffer for the image with hough lines

  for( int i=0; i<dim; i++ ) {
    int loc = i * 3;

    int r = houghPix[loc];
    int g = houghPix[loc+1];
    int b = houghPix[loc+2];

    // if horizontal line has been detected on this row already
    if (yValIgnore == i / w)
      continue;

    /*
     * DETECT HORIZONTAL HOUGH LINE
     * 
     * Detect if the pixels two below and two above are red, alluding to a hough line presence
     */
    if (loc > 3 && r>=230 && pix[loc-6]>=230 && pix[+6]>=230 && loc < dim*3-2)
      yValIgnore = i / w;

    /*
     * DETECT VERTICAL HOUGH LINE
     * Check values 2 pixels back and forward
     *
     * loc > 3 - Ensure we aren't getting out of bounds of pointer
     * r >= 230 - If pixel intersects red hough line
     * pixelDif() - If pixel before and after it are adequately different
     * loc < dim*3-2 - Ensure we aren't getting out of upper bounds of pointer
     */
      if (loc > 3 && r >= 230 && pixelDif(pix[loc-6], pix[loc-5], pix[loc-4], pix[loc+6], pix[loc+7], pix[loc+8] ) && loc < dim*3-2)
        yValDelete = i / w;

      // Catch the remaining pixels after a genuine HL intersection, on the same line
      if (yValDelete == i / w) {
        pix[loc] = 255;
        pix[loc+1] = 255;
        pix[loc+2] = 255;
      }
  }

  imgSeg.update();
}

/*
 * Function to see if the two pixels are adequately different by averging the difference
 * 
 * @param int r1, g1, b1 - respective values of the colour channels of pixel 1
 * @param int r2, g2, b2 - respective values of the colour channels of pixel 2
 * @return bool - returns whether or not the two supplied pixels are 'different'
 */
bool Segment::pixelDif(int r1, int g1, int b1, int r2, int g2, int b2) {
  float r = abs(r1-r2);
  float g = abs(g1-g2);
  float b = abs(b1-b2);

  return (r + g + b) / 3 > 75;
}
