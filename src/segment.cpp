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

using namespace ofxCv;
using namespace cv;

Segment::Segment(ofImage _imgSegH, ofImage _imgSeg, ofPoint _topLeft, int _imageNo): imgSegH(_imgSegH), imgSeg(_imgSeg), topLeft(_topLeft), imageNo(_imageNo), cCount(segCount++) {}

int Segment::segCount = 0;

void Segment::exportSegment() {

  removeBackground();

  string houghName = "seg" + to_string(imageNo) + "/segment" + to_string(cCount) + "-hough.png";
  
  imgSegH.save(houghName, OF_IMAGE_QUALITY_BEST);
}

void Segment::removeBackground() {
  ofImage temp = imgSeg;
  ofImage output;
  Mat img1 = toCv(temp);
  Mat imgGS;

  cvtColor(img1, imgGS, CV_BGR2GRAY);
  threshold(imgGS, imgGS, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

  vector< vector<cv::Point> > contours;
  findContours( imgGS, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
  Mat mask = Mat::zeros( imgGS.rows, imgGS.cols, CV_8UC1 );

  vector<double> areas(contours.size());

  // Find the most prominent contour.
  for(int i = 0; i < contours.size(); i++)
    areas[i] = contourArea(Mat(contours[i]));

  double max;
  cv::Point maxPosition;
  minMaxLoc(Mat(areas),0,&max,0,&maxPosition);
  drawContours(mask, contours, maxPosition.y, Scalar(255), CV_FILLED);

  Mat rgb[3], alphaImage;
  split(img1,rgb);

  Mat rgba[4]={rgb[0],rgb[1],rgb[2],mask};
  merge(rgba,4,alphaImage);

  normalize(mask.clone(), mask, 0.0, 255.0, CV_MINMAX, CV_8UC1);

  toOf( alphaImage, output );
  string name = "seg" + to_string(imageNo) + "/segment" + to_string(cCount) + "-new.png";
  output.save( name );
}
