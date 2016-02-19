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
    vertices.push_back(ofVec2f(90,90));
    vertices.push_back(ofVec2f(0,90));
}

//Returns the number of vertices the shape has
int Shape::getVertexSize(){
    return vertices.size();
}

//Checks if the has been compared
bool Shape::isCompared(){
    return compared;
}

/*
 Compares the the current shape's angles with another shape's angles to see if they are similar.
 
 Order of operations:
 1/-Ensures that both shapes have the same number of vertices.
 2/-Creates temporary angle vectors to contain both shapes angles
 3/-Loops through each of the angles of the current shape compares against each of the angles in the other angle array.
 4/-If the angles which are being compared are within 5 degrees of each other. Those angles are removed from their respective vectors and breaks the current loop to move onto the next angle.
 5/-If none of the angles are similar for any angle then the function will return false.
 6/-The function will return true once all elements of the temporary angle arrays are empty.
*/
bool Shape::compareAngleNoOrder(Shape _shape){
    //1/-
    if(getVertexSize()==_shape.getVertexSize()){
        //2/-
        vector<float> angles, otherAngles;
        angles = getAngleArray();
        otherAngles = _shape.getAngleArray();
        
        //3/-
        for(int i=0; i<angles.size(); i++){
            for(int j=0; j<otherAngles.size(); j++){
                //4/-
                if(abs(angles[i]-otherAngles[j])<5){
                    angles.erase(angles.begin()+i);
                    otherAngles.erase(angles.begin()+j);
                    break;
                }
                else{
                    //5/-
                    if(j==otherAngles.size()-1){
                        return false;
                    }
                }
            }
        }
        //6/-
        return true;
    }
    else{
        return false;
    }
}

bool Shape::compareAngle(Shape _shape){
    //1/-
    if(getVertexSize()==_shape.getVertexSize()){
        //2/-
        vector<float> angles, otherAngles;
        angles = getAngleArray();
        otherAngles = _shape.getAngleArray();
        
        //3/-
        vector<int> firstVertexPos;
        for(int i=0; i<otherAngles.size(); i++){
            if(angles[0]==otherAngles[i]) firstVertexPos.push_back(i);
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
    else{
        return false;
    }
}

bool Shape::checkAnglePos(vector<float> angles, vector<float> otherAngles, int firstPos, int multiplier){
    int nextPos;
    for(int i=1; i<angles.size(); i++){
        nextPos = (firstPos+(i*multiplier))%-(otherAngles.size());
        if(angles[i]!=otherAngles[nextPos]){
            return false;
        }
    }
    return true;
}

//Sets a vertex at a particular point (Used only for testing)
void Shape::setVertex(int i, float x, float y){
    vertices[i]= ofVec2f(x,y);
}

/*
 Creates a vector of floats
 For each vertex, add to vector each angle at those vertices
*/
vector<float> Shape::getAngleArray(){
    vector<float> angles;
    for(int i=0; i<vertices.size(); i++){
        angles.push_back(getAngle(i));
    }
    return angles;
}

//Dot product to get return angle
float Shape::getAngle(int i){
    //Checks next and previous vertices to ensure that program doesn't choose a vertex that is out of bounds to the vertices vector
    int prev,next;
    if(i==0) prev= vertices.size()-1;
    else prev=i-1;
    if(i==vertices.size()) next= 0;
    else next=i+1;
    
    //Creates mathematical vectors between the vertex
    ofVec2f vectorOne = vertices[i]-vertices[prev];
    ofVec2f vectorTwo = vertices[i]-vertices[next];
    
    //Calculates angle between the two mathematical vectors
    float theta = acos((vectorOne.x*vectorTwo.x+vectorOne.y*vectorTwo.y)/(vectorOne.length()*vectorTwo.length()));

    //Returns angle in degrees rather than radians
    return theta*180/PI;
}