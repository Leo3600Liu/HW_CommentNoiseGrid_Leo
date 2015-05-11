//Created by Andreasmuller in 2015.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Utils/ofEasyCamExt.h"

class ofApp : public ofBaseApp      //the basic program starts.
{
public:     //Set up the public
    
    
// --------------------------------
void setup();        //To define the basic environment conditions before the program starts.
    
    
// --------------------------------
void update();       //set up the update
				
// --------------------------------
void draw();     //To excute the code.
    
// --------------------------------
void keyPressed( int _key);     //To set up the keyboard control.
    ofEasyCamExt		camera;     //define camera
    ofMesh				mesh;       //define mesh
    ofxPanel			gui;        //define gui
    
    ofParameter<float>	frequency;      //define frequency
    ofParameter<float>	timeFrequency;      //define time frequency
    
    ofParameter<float>	magnitude;      //define magnitude
    
    ofParameter<float>	gridSize;       //define grid size
    ofParameter<int>	gridResolution;     //define resolution
    
    bool				drawGui;        //define gui
    ofTrueTypeFont		fontSmall;      //define font small
};
