#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    done = false;
    font = new ofTrueTypeFont();
    font->load(OF_TTF_SANS, 10);
    ofEnableSmoothing();
    ofBackground(0);
    
    mainImg.load("long.jpg");
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
    if(!done){
        mainImg.draw(0, 0);
        for(int i=0; i<triangulation.getNumTriangles(); i++){
            vector<ofPoint> points = triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(i));
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofDrawLine(points[0].x, points[0].y, points[1].x, points[1].y);
            ofDrawLine(points[0].x, points[0].y, points[2].x, points[2].y);
            ofDrawLine(points[2].x, points[2].y, points[1].x, points[1].y);
            ofPopStyle();
        }
    }
    else{
        for(int i=0; i<segs.size(); i++){
            segs.at(i).img.draw(segs.at(i).topLeft);
//            ofDrawBitmapString(_seg.img.getColor(mouseX, mouseY), mouseX, mouseY);
        }
    }
    
    for(auto _seg: segs){
        ofPushStyle();
        ofSetColor(_seg.col);
        //                    font->drawString(to_string(_seg.midPoint.x)+" "+to_string(_seg.midPoint.y),_seg.midPoint.x,_seg.midPoint.y);
        ofDrawEllipse(_seg.midPoint.x, _seg.midPoint.y, 10, 10);
        ofPopStyle();
    }
    
    
//    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
    ofDrawBitmapString(to_string(triangulation.getNumTriangles()), ofPoint(10,40));
//
    
//
//    for(auto _seg: segs){
//        ofPushStyle();
//            ofSetColor(_seg.col);
////        ofPoint mid = _seg.getMidPos();
//            font->drawString(to_string(_seg.midPoint.x)+" "+to_string(_seg.midPoint.y),_seg.midPoint.x,_seg.midPoint.y);
//            ofDrawEllipse(_seg.midPoint.x, _seg.midPoint.y, 10, 10);
////            cout<<"Seg: "<<mid<<endl;
//        ofPopStyle();
//    }
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
            segs.push_back(Tri_Segment(points,mainImg));
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
        
        for(auto _s : segs){
            if(_s.otherSeg!=nullptr){
                cout<<_s.midPoint<<" -- "<<_s.otherSeg->midPoint<<endl;
                _s.printAngles();
                _s.otherSeg->printAngles();
            }
        }
        cout<<num<<endl;
    }
    
    if(key=='n'){
//        for(auto _s : segs){
//            _s.createImage(mainImg);
//        }
        done=true;
    }
    
    if(key=='b'){
        done=false;
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
    if(button == OF_MOUSE_BUTTON_LEFT){
        triangulation.addPoint(ofPoint(x,y));
        triangulation.triangulate();
    }
    if(button == OF_MOUSE_BUTTON_RIGHT){
        cout<<"-----NEW-------"<<endl;
        ITRIANGLE tri = triangulation.getTriangleForPos(ofPoint(x,y));
        vector<ofPoint> points = triangulation.getPointsForITriangle(tri);
        for(auto _p: points){
            cout<<_p<<endl;
        }
        cout<<"------------"<<endl;
    }
}
