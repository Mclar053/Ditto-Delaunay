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
    
    mainImg.load("Navona_House.jpg");
        for (int i=0; i<100; i++)
        {
            float x = ofRandom(mainImg.getWidth());
            float y = ofRandom(mainImg.getHeight());
            ofPoint randomPoint(x, y);
            triangulation.addPoint(randomPoint);
        }
    triangulation.triangulate();
    rotBool = false;
    scaBool = false;
    picBool = true;
    num = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(picBool)
        mainImg.draw(0,0);
    if(!done){
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
//        for(int i=0; i<segs.size(); i++){
//        for(auto _seg: segs){
            Tri_Segment& _seg = segs.at(num);
            if(_seg.otherSeg!=nullptr){
                
                //Main Segment
                ofPushMatrix();
                ofTranslate(_seg.midPoint.x, _seg.midPoint.y);
                
                if(rotBool)
                    ofRotate(_seg.getRotation());
                
                if(scaBool)
                    ofScale(_seg.flipped*_seg.scale,_seg.scale,1);
                
                cout<<"Flipped: "<<_seg.flipped<<" Scaled: "<<_seg.scale<<" Rotation: "<<_seg.getRotation()<<endl;
                _seg.img.draw(_seg.topLeft.x-_seg.midPoint.x,_seg.topLeft.y-_seg.midPoint.y);
                
                ofPopMatrix();
                
                //Other Segment
                ofPushMatrix();
                
                ofTranslate(_seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y);
                
                _seg.otherSeg->img.draw(_seg.otherSeg->topLeft.x-_seg.otherSeg->midPoint.x,_seg.otherSeg->topLeft.y-_seg.otherSeg->midPoint.y);
                
                ofPopMatrix();
                
                
                
                ofDrawLine(_seg.midPoint.x, _seg.midPoint.y, _seg.midPoint.x, _seg.midPoint.y-300);
                
                ofDrawLine(_seg.midPoint.x, _seg.midPoint.y, _seg.getAllVertices().at(0).x, _seg.getAllVertices().at(0).y);
                
                
                
                //Draw + midpoint
                //Other
                ofPushStyle();
                    ofSetColor(255, 0, 0);
                    ofDrawEllipse(_seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y,10,10);
                ofPopStyle();
                
                ofPushStyle();
                    ofSetColor(0, 255, 0);
                    ofDrawEllipse(_seg.otherSeg->topLeft.x, _seg.otherSeg->topLeft.y,10,10);
                ofPopStyle();
                
                //Main
                ofPushStyle();
                    ofSetColor(0, 255, 255);
                    ofDrawEllipse(_seg.midPoint.x, _seg.midPoint.y, 10,10);
                ofPopStyle();
                
                ofPushStyle();
                    ofSetColor(0, 0, 255);
                    ofDrawEllipse(_seg.topLeft.x, _seg.topLeft.y, 10,10);
                ofPopStyle();
                
                
                ofPushStyle();
                ofSetColor(255, 255, 0);
                ofDrawLine(_seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y, _seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y-300);
                ofDrawLine(_seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y, _seg.otherSeg->getAllVertices().at(_seg.getFirstVertexPos(_seg.otherSeg->getAllAngles()).at(0)).x, _seg.otherSeg->getAllVertices().at(_seg.getFirstVertexPos(_seg.otherSeg->getAllAngles()).at(0)).y);
                ofPopStyle();
//                break;
                
            }
//        }
    }
    
    //Draw Midpoints
//    for(auto _seg: segs){
//        ofPushStyle();
//        ofSetColor(_seg.col);
//        //                    font->drawString(to_string(_seg.midPoint.x)+" "+to_string(_seg.midPoint.y),_seg.midPoint.x,_seg.midPoint.y);
//        ofDrawEllipse(_seg.midPoint.x, _seg.midPoint.y, 10, 10);
//        ofPopStyle();
//    }
    
    ofDrawBitmapString(to_string(triangulation.getNumTriangles()), ofPoint(10,40));
    
//    ofPushStyle();
//    ofSetColor(0);
//    ofDrawRectangle(0, 0, ofGetWidth(), 50);
//    ofDrawRectangle(0, 0, 50, ofGetHeight());
//    ofDrawRectangle(0, ofGetHeight(), ofGetWidth(), -50);
//    ofDrawRectangle(ofGetWidth(), ofGetHeight(), -50, -ofGetHeight());
//    ofPopStyle();
    
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
        rotBool = false;
        scaBool = false;
    }
    
    if(key=='b'){
        done=!done;
    }
    if(key=='v'){
        rotBool=!rotBool;
    }
    if(key=='c'){
        scaBool=!scaBool;
    }
    if(key=='x'){
        picBool=!picBool;
    }
    if(key=='-'){
        num--;
    }
    if(key=='='){
        num++;
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
