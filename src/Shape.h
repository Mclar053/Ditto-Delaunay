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
    vector<ofVec2f> vertices;
public:
    Shape();
    
    int getVertexSize();
    bool isCompared();
    float getAngle(int i);
    vector<float> getAngleArray();
    bool compare(Shape _shape);
    void checkRotation(Shape _shape);
    
    void setVertex(int i, float x, float y);
    
    float getEdgeLength(int i);
};

#endif /* defined(__shapeTest__Shape__) */
