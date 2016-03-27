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
        cout<<"Vertex "<<i<<": "<<vertices.at(i)<<endl;
        angles.push_back(getAngle(i));
    }
    midPoint = getMidPos();
    resizeImage(_mainImg);
}

void Tri_Segment::printAngles(){
    cout<<"Triangle angles: ";
    cout<<angles[0]<<" "<<angles[1]<<" "<<angles[2]<<endl;
    cout<<"1: "<<vertices[0]<<" 2: "<<vertices[1]<<" 3: "<<vertices[2]<<endl;
//    cout<<angles[0]+angles[1]+angles[2]<<endl;
    /*if(otherSeg!=nullptr){
        cout<<"Other Triangle angles: ";
        cout<<otherSeg->angles[0]<<" "<<otherSeg->angles[1]<<" "<<otherSeg->angles[2]<<endl;
        cout<<"1: "<<otherSeg->vertices[0]<<" 2: "<<otherSeg->vertices[1]<<" 3: "<<otherSeg->vertices[2]<<endl;
    }*/
//    for(int i=0; i<angles.size(); i++){
//        cout<<"Angle "<<i<<": "<<angles.at(i)<<" -- ";
//    }
    cout<<"-----------"<<endl;
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
        
//        cout<<"current::: "<<midPoint<<endl;
//        printAngles();
//        cout<<"other::: "<<_other.midPoint<<endl;
//        _other.printAngles();
        
        //Sets both triangles to compared = true
        //Stops being compared again
        compared = true;
        _other.compared = true;
        
        cout<<"Rotation: "<<getRotationToOther(_other)<<endl;
        cout<<"Match"<<endl;
    } else{
        cout<<"No Match"<<endl;
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

//Gets angle of rotation from the current triangle to the other triangle
float Tri_Segment::getRotationToOther(Tri_Segment& _other){
    vector<int> vertexPositions = getFirstVertexPos(_other.getAllAngles());
    float thetaOne = getAngle(vertices.at(0));
    float thetaTwo = _other.getAngle(_other.vertices.at(vertexPositions.at(0)));
    
    return thetaOne-thetaTwo;
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

float Tri_Segment::getAngle(ofPoint p1){
    ofPoint vectorOne = midPoint-p1;
    ofPoint vectorTwo = midPoint - ofPoint(midPoint.x,midPoint.y-300,0);
    
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));
    
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
        if(abs(angles[0]-_otherAngles[i])<=3)
            firstVertexPos.push_back(i);
    }
    return firstVertexPos;
}

//Resizes the ofImage object to the size of the triangle segment
void Tri_Segment::resizeImage(ofImage& _mainImg){
    //Set top left and bottom right ofPoints to values they are at their max
    topLeft = ofPoint(99999,99999,0);
    bottomRight = ofPoint(0,0,0);
    
    //Go through all vertices and find the top left most point and the bottom right most point
    for(auto _p: vertices){
        if(_p.x<topLeft.x){
            topLeft.x = _p.x;
        }
        if(_p.y<topLeft.y){
            topLeft.y = _p.y;
        }
        
        if(_p.x>bottomRight.x){
            bottomRight.x = _p.x;
        }
        if(_p.y>bottomRight.y){
            bottomRight.y = _p.y;
        }
    }
    
    
    for(auto _v: vertices){
        triangulation.addPoint(_v-topLeft);
//        cout<<"TopLEFT: "<<_v-topLeft<<endl;
    }
    //    triangulation.addPoints(vertices);
    triangulation.triangulate();
    
    
    
    //Set image to the width and height of the triangle
    img.allocate(bottomRight.x-topLeft.x, bottomRight.y-topLeft.y, OF_IMAGE_COLOR_ALPHA);
    for(int i=0; i<img.getWidth(); i++){
        for(int j=0; j<img.getHeight(); j++){
            ITRIANGLE tri = triangulation.getTriangleForPos(ofPoint(i,j));
            vector<ofPoint> _points = triangulation.getPointsForITriangle(tri);
//            cout<<_points[0]<<" "<<_points[1]<<" "<<_points[2]<<endl;
//            cout<<tri.p1<<" "<<tri.p2<<" "<<tri.p3<<endl;
            
            if(tri.p1!=0 || tri.p2!=0 || tri.p3!=0){
                img.setColor(i,j,_mainImg.getColor(i+topLeft.x, j+topLeft.y));
//                cout<<i<<" "<<j<<" Check!!"<<endl;
            }
            else{
                img.setColor(i, j, ofColor(255,255,255,0));
//                cout<<i<<" "<<j<<" NOPE!!"<<endl;
            }
        }
    }
    img.update();
}


void Tri_Segment::createImage(ofImage& _img){
    
//            cout<<_img.getColor(i,j)<<endl;
//            ITRIANGLE tri = triangulation.getTriangleForPos(ofPoint(i,j));
//            if(tri.p1!=0 && tri.p2!=0 && tri.p3!=0){
//            j*img.getWidth()+i
            
//            }
//            else{
//                img.setColor(i,j,ofColor(0,0,0));
//            }
    
}