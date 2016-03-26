//
//  segment.cpp
//  delaunay_test
//
//  Created by Matthew Clark on 21/03/2016.
//
//

#include "triangle-seg.hpp"

Tri_Segment::Tri_Segment(vector<ofPoint> _corners){
    vertices = _corners;
    for(int i=0; i<vertices.size(); i++){
        angles.push_back(getAngle(i));
    }
}

void Tri_Segment::printAngles(){
    cout<<"Triangle angles: ";
    cout<<angles[0]<<" "<<angles[1]<<" "<<angles[2]<<endl;
    cout<<angles[0]+angles[1]+angles[2]<<endl;
    cout<<vertices[0]<<" "<<vertices[1]<<" "<<vertices[2]<<endl;
//    for(int i=0; i<angles.size(); i++){
//        cout<<"Angle "<<i<<": "<<angles.at(i)<<" -- ";
//    }
    cout<<"-----------"<<endl;
}

void Tri_Segment::compare(Tri_Segment _other){
    
}

//Dot product to get return angle
float Tri_Segment::getAngle(int i){
    //Checks next and previous vertices to ensure that program doesn't choose a vertex that is out of bounds to the vertices vector
    int prev,next;
    if(i==0) prev= vertices.size()-1;
    else prev=i-1;
    if(i==vertices.size()-1) next= 0;
    else next=i+1;
    
    //Creates mathematical vectors between the vertex
    ofPoint vectorOne = vertices[i]-vertices[prev];
    ofPoint vectorTwo = vertices[i]-vertices[next];
    
    
    //Calculates angle between the two mathematical vectors
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));
    
    //Returns angle in degrees rather than radians
    return theta*180/PI;
}