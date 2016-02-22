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

Segment::Segment(ofImage _imgSegH, ofImage _imgSeg, ofPoint _topLeft, int _imageNo): imgSegH(_imgSegH), imgSeg(_imgSeg), topLeft(_topLeft), imageNo(_imageNo), cCount(segCount++) {}

int Segment::segCount = 0;

void Segment::exportSegment() {
  removeBackground();
  string name = "seg" + to_string(imageNo) + "/segment" + to_string(cCount) + "-new.png";
  string houghName = "seg" + to_string(imageNo) + "/segment" + to_string(cCount) + "-hough.png";
  
  imgSeg.save(name, OF_IMAGE_QUALITY_BEST);
  imgSegH.save(houghName, OF_IMAGE_QUALITY_BEST);
}

void Segment::removeBackground() {
  w = imgSeg.getWidth();
  h = imgSeg.getHeight();
  int dim = w * h;

  int yValDelete = -1; // stores the y val of the hough line intersection found
  int yValDeleteRef = -1; // stores the last itteration to detect an edge
  int yValIgnore = -1; // stores the y val of a found horizontal hough line to ignore
  bool firstPoint = false; // check to see whether first vertex has been added.

  unsigned char * pix = imgSeg.getPixels(); // Pointer to the start of the pixel buffer for output img
  unsigned char * houghPix = imgSegH.getPixels(); // Pointer to the start of the pixel buffer for the image with hough lines

  for( int i=0; i<dim; i++ ) {
    int loc = i * 3;
    int row = i / w;

    int r = houghPix[loc];
    int g = houghPix[loc+1];
    int b = houghPix[loc+2];

    // Catch the remaining pixels after a genuine HL intersection, on the same line
    if (row == yValDelete) {
      pix[loc] = 255;
      pix[loc+1] = 255;
      pix[loc+2] = 255;
      continue;
    }

    /**
     * ARE WE IN POINTER'S BOUNDS?
     * 
     * loc > 3 - Ensure we aren't getting out of bounds of pointer
     * loc < dim*3-2 - Ensure we aren't getting out of upper bounds of pointer
     */
    if (loc > 3 && loc < dim*3-2) {
      /*
       * DETECT HORIZONTAL HOUGH LINE
       * 
       * Detect if the pixels two below and two above are red, alluding to a hough line presence
       * - First check if there's a 'red' pixel
       * - Then check if the pixel and the next are the same
       * - Then check if pixel and the one before are the same
       */
      if (r>=200 && g<=75 && b<=75 &&
          !(pixelDif(pix[loc], pix[loc+1], pix[loc+2], pix[loc+3], pix[loc+4], pix[loc+5], 20)) &&
          !(pixelDif(pix[loc], pix[loc+1], pix[loc+2], pix[loc-3], pix[loc-2], pix[loc-1], 20))) {
        yValIgnore = row;
        continue;
      } // End Horizontal check

      /*
       * DETECT VERTICAL HOUGH LINE
       * Check values 2 pixels back and forward
       *
       * r >= 225 - If pixel intersects red hough line
       * (i + 1) / 3 / w == row && - Ensure the pixels are on the same row
       * (i - 1) / 3 / w == row && - ^
       * pixelDif() - If pixel before and after it are adequately different
       */
      if(r>=200 && g<=75 && b<=75 &&
        (i + 1) / w == row &&
        (i - 1) / w == row &&
        pixelDif(pix[loc-3], pix[loc-2], pix[loc-1], pix[loc+3], pix[loc+4], pix[loc+5], 15)) {
        if(!firstPoint) addVertex(i, row); // Add the first edge
        yValDelete = row;
        yValDeleteRef = i;
      } // End vertical check

    }

  }

  addVertex(yValDeleteRef, yValDelete); // Add the last detected edge post-loop

  imgSeg.update();
}

/*
 * Function to see if the two pixels are adequately different by averging the difference
 * 
 * @param int r1, g1, b1 - respective values of the colour channels of pixel 1
 * @param int r2, g2, b2 - respective values of the colour channels of pixel 2
 * @return bool - returns whether or not the two supplied pixels are 'different'
 */
bool Segment::pixelDif(int r1, int g1, int b1, int r2, int g2, int b2, int diff) {
  float r = abs(r1-r2);
  float g = abs(g1-g2);
  float b = abs(b1-b2);

  return (r + g + b) / 3 > diff;
}

/**
 * ADD VERTEX
 * Used to map an index of the array to a point in of space
 *
 * @param int i - the position in the pixel pointer array
 * @param int row - the y value of the pixel in of terms
 */
void Segment::addVertex(int i, int row) {
  int x = (i%w)+1;
  edges.push_back(ofPoint(x, row));
}
