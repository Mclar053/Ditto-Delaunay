//
//  segment.cpp
//  delaunay_test
//
//  Created by Matthew Clark on 21/03/2016.
//
//

#include "triangle-seg.hpp"

Tri_Segment::Tri_Segment(vector<ofPoint> _corners): compared(false){
    vertices = _corners;
    for(int i=0; i<vertices.size(); i++){
        cout<<"Vertex "<<i<<": "<<vertices.at(i)<<endl;
        angles.push_back(getAngle(i));
    }
    midPoint = getMidPos();
}

void Tri_Segment::printAngles(){
    cout<<"Triangle angles: ";
    cout<<angles[0]<<" "<<angles[1]<<" "<<angles[2]<<endl;
    cout<<angles[0]+angles[1]+angles[2]<<endl;
    cout<<"1: "<<vertices[0]<<" 2: "<<vertices[1]<<" 3: "<<vertices[2]<<endl;
//    for(int i=0; i<angles.size(); i++){
//        cout<<"Angle "<<i<<": "<<angles.at(i)<<" -- ";
//    }
    cout<<"-----------"<<endl;
}
//Compares 2 triangle segements
//Takes Another triangle segment as argument
void Tri_Segment::compare(Tri_Segment _other){
    //Ensures that the segment has not been compared already
    //and is the same/similar to the other triangle segment
    if(compareAngles(_other)&& !_other.compared){
        //Sets random colour to the current triangle and the other to identify what has been compared
        ofColor randomCol = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        col = randomCol;
        _other.col = randomCol;
        
        //Sets both triangles to compared = true
        //Stops being compared again
        compared = true;
        _other.compared = true;
        cout<<"Match"<<endl;
    } else{
        cout<<"No Match"<<endl;
    }
    
}

//Compares angles between 2 triangles
//Take another triangle segment as argument
//Return true or false whether the angles match
bool Tri_Segment::compareAngles(Tri_Segment _other){
    
        //1/-
        vector<float> otherAngles;
        otherAngles = _other.getAllAngles();
        
        //2/-
        vector<int> firstVertexPos;
        for(int i=0; i<otherAngles.size(); i++){
            if(abs(angles[0]-otherAngles[i])<=3) firstVertexPos.push_back(i);
        }
        
        //3/-
        for(int _vertex : firstVertexPos){
            if(checkAnglePos(angles, otherAngles, _vertex,1)){
                return true;
            }
            if(checkAnglePos(angles, otherAngles, _vertex,-1)){
                return true;
            }
        }
        return false;
}

//Checks the angles of the current triangle angle array and the other triangle angle array
//Returns true if all angles are within 3 degrees of each other
//Returns false if any angles are over 3 degrees of each other
bool Tri_Segment::checkAnglePos(vector<float> _angles, vector<float> _otherAngles, int _firstPos, int _multiplier){
    int nextPos;
    for(int i=1; i<angles.size(); i++){
        nextPos = (_firstPos+(i*_multiplier))%-(_otherAngles.size());
        if(abs(angles[i]-_otherAngles[nextPos])>3){
            return false;
        }
    }
    return true;
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

//Gets the mid point of the current triangle segment
//Adds all the vertices together and divides by the number of vertices (in this case 3)
//Returns the midpoint of the current triangle - ofPoint type
ofPoint Tri_Segment::getMidPos(){
    
    float x, y;
    
    x = (vertices.at(0).x + vertices.at(1).x + vertices.at(2).x)/3;
    y = (vertices.at(0).y + vertices.at(1).y + vertices.at(2).y)/3;
    
    ofPoint mid = ofPoint(x,y,0);
    
    return mid;
}

//Gets angle of rotation from one triangle to the other triangle which has been compared to
float Tri_Segment::getRotationToOther(Tri_Segment _other){
    
}