#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    font = new ofTrueTypeFont();
    font->load(OF_TTF_SANS, 10);
    ofEnableSmoothing();
    ofBackground(0);
    //    for (int i=0; i<300; i++)
    //    {
    //        float x = ofRandom(ofGetWidth());
    //        float y = ofRandom(ofGetHeight());
    //        ofPoint randomPoint(x, y);
    //        triangulation.addPoint(randomPoint);
    //    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
//        triangulation.draw();
    ofPopStyle();
    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
    
    for(int i=0; i<triangulation.getNumTriangles(); i++){
        vector<ofPoint> points = triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(i));
        ofDrawLine(points[0].x, points[0].y, points[1].x, points[1].y);
        ofDrawLine(points[0].x, points[0].y, points[2].x, points[2].y);
        ofDrawLine(points[2].x, points[2].y, points[1].x, points[1].y);
        font->drawString(to_string(points[0].x)+" "+to_string(points[0].y), points[0].x, points[0].y);
        font->drawString(to_string(points[1].x)+" "+to_string(points[1].y), points[1].x, points[1].y);
        font->drawString(to_string(points[2].x)+" "+to_string(points[2].y), points[2].x, points[2].y);
    }
    
    for(auto _seg: segs){
        ofPushStyle();
            ofSetColor(_seg.col);
//        ofPoint mid = _seg.getMidPos();
            font->drawString(to_string(_seg.midPoint.x)+" "+to_string(_seg.midPoint.y),_seg.midPoint.x,_seg.midPoint.y);
            ofDrawEllipse(_seg.midPoint.x, _seg.midPoint.y, 10, 10);
//            cout<<"Seg: "<<mid<<endl;
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        segs.clear();
        triangulation.reset();
    }
    if(key=='l'){
        segs.clear();
        vector<ofPoint> points;
        for(int i=0; i<triangulation.getNumTriangles(); i++){
            points.clear();
            points = triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(i));
            for(auto _p: points)
                cout<<_p<<endl;
            segs.push_back(Tri_Segment(points));
            segs.at(i).printAngles();
        }
        
    }
    if(key=='m'){
        int num = 0;
        for(int i=0; i<segs.size(); i++){
            for(int j=i+1; j<segs.size(); j++){
                segs.at(i).compare(segs.at(j));
                num++;
            }
        }
        cout<<num<<endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    triangulation.addPoint(ofPoint(x,y));
    triangulation.triangulate();
}
