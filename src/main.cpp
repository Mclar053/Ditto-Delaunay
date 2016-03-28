#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char * argv[] ) {
	ofSetupOpenGL(1024, 650, OF_WINDOW);
  ofApp * app = new ofApp();


  ofRunApp(app);
}
