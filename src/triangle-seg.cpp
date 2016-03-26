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
    if(compareAngles(_other)&& !_other.compared){
        ofColor randomCol = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        col = randomCol;
        _other.col = randomCol;
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
    
        //2/-
        vector<float> otherAngles;
        otherAngles = _other.getAllAngles();
        
        //3/-
        vector<int> firstVertexPos;
        for(int i=0; i<otherAngles.size(); i++){
            if(abs(angles[0]-otherAngles[i])<=3) firstVertexPos.push_back(i);
        }
        
        //4/-
        
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

ofPoint Tri_Segment::getMidPos(){
//    ofPoint midPoint = vertices.at(0).middle(vertices.at(1));
    
    float x, y;
    
    for(auto _vertex: vertices){
        cout<<"Vertex: "<<_vertex<<endl;
    }
    cout<<"------"<<endl;
    x = (vertices.at(0).x + vertices.at(1).x + vertices.at(2).x)/3;
    y = (vertices.at(0).y + vertices.at(1).y + vertices.at(2).y)/3;
    
    ofPoint mid = ofPoint(x,y,0);
    cout<<mid<<endl;
    
    return mid;
}