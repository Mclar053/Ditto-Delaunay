//
//  Shape.cpp
//  shape_segmentation_test
//
//  Created by Matthew Clark on 18/01/2016.
//
//

#include "Shape.h"

Shape::Shape(){
    vertices.push_back(ofVec2f(0,0));
    vertices.push_back(ofVec2f(90,0));
    vertices.push_back(ofVec2f(45,45));
}

int Shape::getVertexSize(){
    return vertices.size();
}

bool Shape::isCompared(){
    return compared;
}

bool Shape::compare(Shape _shape){
    if(getVertexSize()==_shape.getVertexSize()){
        vector<float> angles, otherAngles;
        angles = getAngleArray();
        otherAngles = _shape.getAngleArray();
        
        for(int i=0; i<angles.size(); i++){
            for(int j=0; j<otherAngles.size(); j++){
                if(abs(angles[i]-otherAngles[j])<5){
                    angles.erase(angles.begin()+i);
                    otherAngles.erase(angles.begin()+j);
                    break;
                }
                else{
                    if(j==otherAngles.size()-1){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

void Shape::setVertex(int i, float x, float y){
    vertices[i]= ofVec2f(x,y);
}

vector<float> Shape::getAngleArray(){
    vector<float> angles;
    for(int i=0; i<vertices.size(); i++){
        angles.push_back(getAngle(i));
    }
    return angles;
}

float Shape::getAngle(int i){
    int prev,next;
    if(i==0) prev= vertices.size()-1;
    else prev=i-1;
    if(i==vertices.size()) next= 0;
    else next=i+1;
    
    ofVec2f vectorOne = vertices[i]-vertices[prev];
    ofVec2f vectorTwo = vertices[i]-vertices[next];
    
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));
    return theta*180/PI;
}