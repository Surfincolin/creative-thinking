#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxGui.h"
#include "CameraHandler.hpp"
#include "ImageHandler.hpp"
#include "GaussianBlur.hpp"

class ofApp : public ofBaseApp{
  
  int w = 1280;
  int h = 720;
  
  int fN = 7;
  
  ct::CameraHandler *cameraHandler = new ct::CameraHandler();
  ct::ImageHandler imageHandler;
  
  ofxPanel gui;
  ofxIntSlider lowerThreshold;
  ofxIntSlider upperThreshold;
  ofxIntSlider blurPasses;
  bool hideGui;

  //shared_ptr<ct::GaussianBlur> gBlur;
  
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
  
    ofVideoGrabber cam;
  
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grey;
    ofxCvGrayscaleImage invertedGrey;
    ofxCvGrayscaleImage canny;
    ofxCvColorImage hsb;
  
  
    ofxCvHaarFinder faces;
  
  ofImage pic;
  ofImage img;
  ofPlanePrimitive plane;
  
  bool snapshot;
  
  ofShader chromaticShader;
  ofShader colorDodge;
  ofShader findEdge;

  
  ofFbo edgePassFbo;
//  ofFbo fboPassTwo;
  ofFbo fboDodge;
  
};
