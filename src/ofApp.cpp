#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    done = false;
    ofEnableSmoothing();
    ofBackground(0);
    
    //Load main image
    mainImg.load("tudor_house.jpg");
    
    
    int thresh = 130; //CHANGE THIS VALUE FOR MORE/LESS SEGMENTS
    int max_thresh = 255;

    
    /*
     Open Cv Harris Corner Detetction
     Reference: http://docs.opencv.org/2.4/doc/tutorials/features2d/trackingmotion/harris_detector/harris_detector.html
     */
    src = toCv(mainImg);
    cvtColor( src, src_gray, CV_BGR2GRAY );
    
    Mat dst, dst_norm, dst_norm_scaled;
    dst = Mat::zeros( src.size(), CV_32FC1 );
    
    /// Detector parameters
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    
    /// Detecting corners
    cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
    
    /// Normalizing
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    
    /// Adding x y point to triangulation
    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
    {
        if( (int) dst_norm.at<float>(j,i) > thresh )
        {
            ofPoint point(i, j);
            triangulation.addPoint(point);
        }
    }
    }
    
    //Triangulate all corners to triangles
    triangulation.triangulate();
    cout<<"done triangulation"<<endl;
    
    //Create segments
    segs.clear();
    vector<ofPoint> points;
    
    //For each triangle in triangulation object
    //Clear points, get corners for selected triangle and add points to new triangle segment
    for(int i=0; i<triangulation.getNumTriangles(); i++){
        points.clear();
        points = triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(i));
        for(auto _p: points)
            segs.push_back(Tri_Segment(points,mainImg));
    }
    cout<<"done segmentation"<<endl;
    
    //Compare each segment against each other triangle segment
    for(int i=0; i<segs.size(); i++){
        for(int j=i+1; j<segs.size(); j++){
            segs.at(i).compare(segs.at(j));
        }
    }
    cout<<"done comparision"<<endl;
    
    done=true;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    //Check if the image has been created
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
        
        //Loops through all segments
        for(auto _seg: segs){
            //Check if the segment has a match
            if(_seg.otherSeg!=nullptr){
                
                ofPushMatrix();
                    ofTranslate(_seg.otherSeg->midPoint.x, _seg.otherSeg->midPoint.y);
                    ofRotate(_seg.getRotation());
                    ofScale(_seg.flipped*_seg.scale,_seg.scale,1);
                    _seg.img.draw(_seg.otherSeg->topLeft.x-_seg.otherSeg->midPoint.x,_seg.otherSeg->topLeft.y-_seg.otherSeg->midPoint.y);
                ofPopMatrix();
            }
        }
    }
    
    //Number of triangle segments
    //ofDrawBitmapString(to_string(triangulation.getNumTriangles()), ofPoint(10,40));
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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

}
