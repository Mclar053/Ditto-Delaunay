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
#include "ofxDelaunay.h"

class Tri_Segment{
    vector<ofPoint> vertices;
    vector<float> angles;
    ofxDelaunay triangulation;
    
    bool compareAngles(Tri_Segment& _other);
    float getRotationToOther(Tri_Segment& _other);
    
    vector<int> getFirstVertexPos(vector<float> _otherAngles);
    ofPoint getMidPos();
    
    
    
    
public:
    Tri_Segment(vector<ofPoint> _corners, ofImage& _mainImg);
    
    ofPoint midPoint;
    ofColor col;
    bool compared;
    ofImage img;
    Tri_Segment* otherSeg;
    ofPoint topLeft, bottomRight;
    
    void compare(Tri_Segment& _other);
    float getAngle(int i);
    float getAngle(ofPoint p1);
    void printAngles();
    
    vector<float> getAllAngles(){
        return angles;
    };

    void resizeImage(ofImage& _mainImg);
    void createImage(ofImage& _img);
    
    bool checkAnglePos(vector<float> angles, vector<float> otherAngles, int firstPos, int multiplier);
};

#endif /* segment_hpp */
