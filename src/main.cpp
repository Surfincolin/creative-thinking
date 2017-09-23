#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//	ofRunApp(new ofApp());
  
  
  ofGLFWWindowSettings settings;
  settings.setGLVersion(3, 2); //we define the OpenGL version we want to use
  settings.width = 1280;
  settings.height = 720;
//  settings.windowMode = OF_FULLSCREEN;
//  settings.monitor = 1;
//  settings.multiMonitorFullScreen = true;
  ofCreateWindow(settings);
//  // this kicks off the running of my app
  ofRunApp(new ofApp());

}
