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

class Tri_Segment{
    vector<ofPoint> vertices;
    vector<float> angles;
    ofImage img;
    
    bool compareAngles(Tri_Segment& _other);
    float getRotationToOther(Tri_Segment& _other);
    
    vector<int> getFirstVertexPos(vector<float> _otherAngles);
    ofPoint getMidPos();
    
    
public:
    Tri_Segment(vector<ofPoint> _corners);
    
    ofPoint midPoint;
    ofColor col;
    bool compared;
    Tri_Segment* otherSeg;
    
    void compare(Tri_Segment& _other);
    float getAngle(int i);
    float getAngle(ofPoint p1);
    void printAngles();
    
    vector<float> getAllAngles(){
        return angles;
    };

    
    bool checkAnglePos(vector<float> angles, vector<float> otherAngles, int firstPos, int multiplier);
};

#endif /* segment_hpp */
