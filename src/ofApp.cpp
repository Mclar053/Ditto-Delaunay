#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
  Architecture img = Architecture("http://www.tekuto.com/wp-content/themes/tekuto2nd/images/topmain/toruso01.jpg?=20151006");
  Architecture img2 = Architecture("long.jpg");

  images.push_back(img);
  images.push_back(img2);

  Architecture::findBestMatches(images.at(0), images.at(1));
}

void ofApp::update() {};

void ofApp::draw() {
  images.at(toDisplay).drawImage();

  // Draw all the best segment replacements in place of the old ones.
  for ( auto const & seg : images.at(0).segments ) {
    if ( seg.bestSegMatch != nullptr )
      seg.bestSegMatch->imgFinal.draw(seg.topLeft);
  }
}

void ofApp::mousePressed(int x, int y, int button) {}

void ofApp::keyPressed(int key) {
  if (key == OF_KEY_RETURN) {
    // Loop through the pictures
    (toDisplay < images.size()-1) ? toDisplay ++ : toDisplay = 0;
  } else if (key == OF_KEY_RIGHT) {
    // loop incrementally through the second photo's segments.
    (toCompare.y < images.at(1).segments.size()-1) ? toCompare.y ++ : toCompare.y = 0;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  } else if (key == OF_KEY_LEFT) {
    // loop decremently through the second photo's segments.
    (toCompare.y > 0) ? toCompare.y -- : toCompare.y = images.at(1).segments.size()-1;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  } else if (key == OF_KEY_UP) {
    // loop incrementally through first photo's segments.
    (toCompare.x < images.at(0).segments.size()-1) ? toCompare.x ++ : toCompare.x = 0;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  } else if (key == OF_KEY_DOWN) {
    // loop decrementally through first photo's segments.
    (toCompare.x > 0) ? toCompare.x -- : toCompare.x = images.at(0).segments.size()-1;

    Segment::compareSegs(images.at(0).segments.at(toCompare.x), images.at(1).segments.at(toCompare.y));
  }
}
