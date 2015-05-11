//Created by Andreasmuller in 2015.

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    ofSetupOpenGL(1024,768, OF_WINDOW);     //The screen size is 1024*768.
    // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new ofApp());    
}
