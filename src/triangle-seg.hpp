//
//  segment.hpp
//  delaunay_test
//
//  Created by Matthew Clark on 21/03/2016.
//
//

#ifndef segment_hpp
#define segment_hpp

#include <stdio.h>
#include "../ofMain.h"

class Segment{
    vector<ofPoint> vertices;
    vector<float> angles;
    ofImage img;
public:
    Segment(vector<ofPoint> _corners);
    
    void compare(Segment _other);
    float getAngle(int i);
    void printAngles();
};

#endif /* segment_hpp */
