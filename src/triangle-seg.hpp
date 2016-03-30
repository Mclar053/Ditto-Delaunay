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
    float rotation;
    
    bool compareAngles(Tri_Segment& _other);
    float getRotationToOther(Tri_Segment& _other);
    float getScaleToOther(Tri_Segment& _other);
    
    
    ofPoint getMidPos();
    
    
    
    
public:
    Tri_Segment(vector<ofPoint> _corners, ofImage& _mainImg);
    
    ofPoint midPoint;
    ofColor col;
    bool compared;
    ofImage img;
    Tri_Segment* otherSeg;
    ofPoint topLeft, bottomRight;
    int flipped;
    float scale;
    
    void compare(Tri_Segment& _other);
    float getAngle(int i);
    float getAngle(ofPoint p1);
    bool checkAnglePos(vector<float> angles, vector<float> otherAngles, int firstPos, int multiplier);
    
    
    void printAngles();
    
    vector<float> getAllAngles(){
        return angles;
    };
    
    vector<ofPoint> getAllVertices(){
        return vertices;
    }
    
    vector<int> getFirstVertexPos(vector<float> _otherAngles);
    
    float getRotation(){
        return rotation;
    }

    void createImage(ofImage& _mainImg);
};

#endif /* segment_hpp */
