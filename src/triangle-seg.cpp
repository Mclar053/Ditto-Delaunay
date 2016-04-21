//
//  segment.cpp
//  delaunay_test
//
//  Created by Matthew Clark on 21/03/2016.
//
//

#include "triangle-seg.hpp"

Tri_Segment::Tri_Segment(vector<ofPoint> _corners, ofImage& _mainImg): compared(false){
    vertices = _corners;
    col = ofColor(255);
    otherSeg = nullptr;
    for(int i=0; i<vertices.size(); i++){
        angles.push_back(getAngle(i));
    }
    midPoint = getMidPos();
    rotation = 0;
    flipped = 1;
    createImage(_mainImg);
}

//Compares 2 triangle segements
//Takes Another triangle segment as argument
void Tri_Segment::compare(Tri_Segment& _other){
    //Ensures that the segment has not been compared already
    //and is the same/similar to the other triangle segment
    if(compareAngles(_other)&& !_other.compared){
        //Sets random colour to the current triangle and the other to identify what has been compared
        ofColor randomCol = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        
        col = randomCol;
        _other.col = randomCol;
        otherSeg = &_other;
        
        //Sets both triangles to compared = true
        //Stops being compared again
        compared = true;
        _other.compared = true;
        
        rotation = getRotationToOther(_other);
        scale = getScaleToOther(_other);
    } else{
//        cout<<"No Match"<<endl;
    }
    
}

//Compares angles between 2 triangles
//Take another triangle segment as argument
//Return true or false whether the angles match
bool Tri_Segment::compareAngles(Tri_Segment& _other){
    
        //1/-
        vector<float> otherAngles;
        otherAngles = _other.getAllAngles();
        
        //2/-
        vector<int> firstVertexPos = getFirstVertexPos(otherAngles);
        
        //3/-
        for(int _vertex : firstVertexPos){
            if(checkAnglePos(angles, otherAngles, _vertex,1)){
                flipped = 1;
                return true;
            }
            if(checkAnglePos(angles, otherAngles, _vertex,-1)){
                flipped = -1;
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
        if(abs(angles[i]-_otherAngles[nextPos])>1){
            return false;
        }
    }
    return true;
}

//Gets angle of rotation from the current triangle to the other triangle
float Tri_Segment::getRotationToOther(Tri_Segment& _other){
    vector<int> vertexPositions = getFirstVertexPos(_other.getAllAngles());
    float thetaOne = getAngle(vertices.at(0));
    float thetaTwo = _other.getAngle(_other.vertices.at(vertexPositions.at(0)));
    
    float thetaThree = 360 - thetaOne + thetaTwo;
    return thetaThree;
}

float Tri_Segment::getScaleToOther(Tri_Segment& _other){
    vector<int> vertexPositions = getFirstVertexPos(_other.getAllAngles());
    ofPoint vectorOne = ofPoint(abs(vertices.at(0).x-vertices.at(1).x),abs(vertices.at(0).y-vertices.at(1).y));
    ofPoint vectorTwo = ofPoint(abs(_other.vertices.at(vertexPositions.at(0)).x-_other.vertices.at((vertexPositions.at(0)+1)%3).x),abs(_other.vertices.at(vertexPositions.at(0)).y-_other.vertices.at((vertexPositions.at(0)+1)%3).y));
    
    return vectorTwo.length()/vectorOne.length();
}

//Dot product to get return angle based on index of the vertices vector
float Tri_Segment::getAngle(int i){
    //Checks next and previous vertices to ensure that program doesn't choose a vertex that is out of bounds to the vertices vector
    int prev,next;
    if(i==0) prev= vertices.size()-1;
    else prev=i-1;
    if(i==vertices.size()-1) next= 0;
    else next=i+1;
    
    //Creates mathematical vectors between the vertex
    ofPoint vectorOne = vertices[prev]-vertices[i];
    ofPoint vectorTwo = vertices[next]-vertices[i];
    
    
    //Calculates angle between the two mathematical vectors
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));
    
    //Returns angle in degrees rather than radians
    return theta*180/PI;
}

//Gets angle based on an x,y coordinate to a verticle like
float Tri_Segment::getAngle(ofPoint p1){
    ofPoint vectorOne = p1-midPoint;
    ofPoint vectorTwo = ofPoint(midPoint.x,midPoint.y-300,0)- midPoint;
    
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));

    if((vectorOne.x<0 && vectorOne.y<0) || (vectorOne.x<0 && vectorOne.y>0)) theta = -theta;
    
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

vector<int> Tri_Segment::getFirstVertexPos(vector<float> _otherAngles){
    vector<int> firstVertexPos;
    for(int i=0; i<_otherAngles.size(); i++){
        if(abs(angles[0]-_otherAngles[i])<=1)
            firstVertexPos.push_back(i);
    }
    return firstVertexPos;
}

//Finds the top-left most and bottom-right most points of the triangle to allocate space to the ofImage object (img)
//Resizes the ofImage object to the size of the triangle segment
//Creates the image for the triangle segment from the main image
void Tri_Segment::createImage(ofImage& _mainImg){
    //Set top left and bottom right ofPoints to values they are at their max
    topLeft = ofPoint(99999,99999,0);
    bottomRight = ofPoint(0,0,0);
    
    //Go through all vertices and find the top left most point and the bottom right most point
    for(auto _p: vertices){
        if(_p.x<topLeft.x){ //Left most point
            topLeft.x = _p.x;
        }
        if(_p.y<topLeft.y){ //Top most point
            topLeft.y = _p.y;
        }
        
        if(_p.x>bottomRight.x){ //Right most point
            bottomRight.x = _p.x;
        }
        if(_p.y>bottomRight.y){ //Bottom most point
            bottomRight.y = _p.y;
        }
    }
    
    //Add points to the triangulation ofxDelaunay object
    for(auto _v: vertices){
        triangulation.addPoint(_v-topLeft); //Add each vertex minus the topLeft of the image for easy comparison
    }
    triangulation.triangulate(); //Create triangle for triangulation
    
    
    //Set image to the width and height of the triangle
    img.allocate(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y, OF_IMAGE_COLOR_ALPHA);
    for(int i=0; i<img.getWidth(); i++){
        for(int j=0; j<img.getHeight(); j++){
            
            //Find an ITRANGLE for the x,y position in the img
            ITRIANGLE tri = triangulation.getTriangleForPos(ofPoint(i,j));
            
            //If there is a triangle
            if(tri.p1!=0 || tri.p2!=0 || tri.p3!=0){
                img.setColor(i,j,_mainImg.getColor(i+topLeft.x, j+topLeft.y)); //Sets the pixel colour to the colour of the image at the segments position
            }
            else{ //If not
                img.setColor(i, j, ofColor(255,255,255,0)); //Set colour to black with 0% opacity
            }
        }
    }
    img.update(); //Update the image pixel array
}