//
//  Shape.h
//  shape_segmentation_test
//
//  Created by Matthew Clark on 18/01/2016.
//
//

#ifndef __shapeTest__Shape__
#define __shapeTest__Shape__

#include "ofMain.h"
#include <stdio.h>
class Shape{
    bool compared;
    bool flipped;
    vector<ofVec2f> vertices;
public:
    Shape();
    
    int getVertexSize();
    bool isCompared();
    bool isFlipped();
    float getAngle(int i);
    vector<float> getAngleArray();
    bool compareAngleNoOrder(Shape _shape); //Checks shape angles in no particular order
    bool compareAngle(Shape _shape);
    
    
    float getSizeRatio(Shape _shape);
    float checkRotation(Shape _shape);
    
    void setVertex(int i, float x, float y);
    
    float getEdgeLength(int i);
};

#endif /* defined(__shapeTest__Shape__) */
