//Created by Andreasmuller in 2015.

#include <ofApp.h>
void ofApp::setup()        //To define the basic environment conditions before the program starts.
{
    fontSmall.loadFont("Fonts/DIN.otf", 8 );        //load the file into the project
    
    ofxGuiSetFont( "Fonts/DIN.otf", 8 );        //set up the gui of that file
    ofxGuiSetDefaultWidth( 260 );       //set up the with of gui
    
    string xmlSettingsPath = "Settings/NoiseGrid.xml";      //load the file
    gui.setup( "Noise Grid", xmlSettingsPath );     //set up the Gui of the file
    
    gui.add( frequency.set("Frequency",  1.0f,  0.01f,  2.0f) );        //gui frequency
    gui.add( timeFrequency.set("Time Frequency",  1.0f,  0.001f,  3.0f) );      //time gui frequency
    gui.add( magnitude.set("Magnitude",  0.3f,  0.0f,  5.0f) );     //gui magnitude
    
    gui.add( gridSize.set("Grid Size",  6.0f,  0.01f,  20.0f) );    //gui grid size
    gui.add( gridResolution.set("Grid Resolution",  20,  3,  100) );    //gui grid resolution
    
    gui.loadFromFile( xmlSettingsPath );        // gui load the file "xmlSettingsPath"
    
    camera.setAutoDistance( false );        //the distance of the animation
    camera.setGlobalPosition( ofVec3f(0,5,-10) );       //the position of the animation
    camera.lookAt( ofVec3f(0,3,0) );        //set up the vector
    camera.setNearClip( 0.0001f );      //set up the frequency of clip
    camera.setFarClip( 512 );       //make the animation more soft
    
    drawGui = true;     //make the gui work
}

// --------------------------------
void ofApp::update()       //set up the update
{
    float time = ofGetElapsedTimef();       //define "time"
    float noiseTime = time * timeFrequency;     //define "noiseTime"
    
    ofVec3f extentMin( gridSize * -0.5, 0,		  gridSize * -0.5 );        //set up the minmum
    ofVec3f extentMax( gridSize *  0.5, gridSize, gridSize *  0.5 );        //set up the maxmum
    
    mesh.clear();       //clean up the background
    mesh.setMode( OF_PRIMITIVE_LINES );     //set uo the Mode
    
    for( int y = 0; y < gridResolution; y++ )       //set the grid resolution y
    {
        for( int x = 0; x < gridResolution; x++ )       //set the grid resolution x
        {
            for( int z = 0; z < gridResolution; z++ )       //set the grid resolution z
            {
                ofVec3f pos;        //set up those three vectors' position
                
                pos.x = ofMap( x,  0, gridResolution-1, extentMin.x, extentMax.x );     //the position of x in map
                pos.y = ofMap( y,  0, gridResolution-1, extentMin.y, extentMax.y );     //the position of y in map
                pos.z = ofMap( z,  0, gridResolution-1, extentMin.z, extentMax.z );     //the position of z in map
                
                ofVec3f noisePos = pos * frequency;     //the creation of noise
                
                ofVec3f vel;        //set up the velocity
                vel.x = ofSignedNoise( noisePos.x, noisePos.y, noisePos.z, noiseTime );     //the velocity of x
                vel.y = ofSignedNoise( noiseTime,  noisePos.z, noisePos.y, noisePos.x );        //the velocity of y
                vel.z = ofSignedNoise( noisePos.z, noiseTime,  noisePos.y, noisePos.x );        //the velocity of z
                
                ofVec3f normVel = vel.getNormalized();      //define the velocity of those three vectors
                ofVec3f velAsCol = (normVel + ofVec3f(1)) * 0.5;        //define the velocity of those three vectors
                
                
                // Color by direction
                ofFloatColor tmpCol( velAsCol.x, velAsCol.y, velAsCol.z );      //color's direction
                
                mesh.addVertex( pos );      //color's position
                mesh.addColor( tmpCol );        //add more color
                
                mesh.addVertex( pos + (vel * magnitude));       //add vectors into it
                mesh.addColor( ofFloatColor(tmpCol, 0.0) );     //add more color
            }
        }
    }
}

// --------------------------------
void ofApp::draw()     //To excute the code.
{
    ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);     //the color of the background
    
    ofEnableDepthTest();        //set up the Enable Depth Test
    
    camera.begin();     //begin to draw
    
    // draw a grid on the floor
    ofSetColor( ofColor(60) );      //set up the color
    ofPushMatrix();     //push matrix
    ofRotate(90, 0, 0, -1);     //set up the rotate
    ofDrawGridPlane( 10, 10, false );       //draw the plane
	ofPopMatrix();      //pop matrix
    
	ofSetColor( ofColor::white );       //set up the color
	//ofDrawBox( 1.0f );
	mesh.draw();        //make the draw work
    
    camera.end();       //end up the camera
    
    ofDisableDepthTest();       //open the test code
    if( drawGui ) { gui.draw(); }       //set up the if
    
    ofSetColor( ofColor::black );       //set up the color
    fontSmall.drawString( ofToString(ofGetFrameRate(), 1), ofGetWidth() - 25, ofGetHeight() - 5 );      //draw the string
}

// --------------------------------
void ofApp:: keyPressed( int _key )     //To set up the keyboard control.
{
    if( _key == ' ' )			  { }       //space button
    else if( _key == OF_KEY_TAB ) { drawGui = !drawGui; }       //tab button
    else if( _key == 'f' )		  { ofToggleFullscreen(); }     //f button
}
