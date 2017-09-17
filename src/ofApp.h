#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxGui.h"
#include "CameraHandler.hpp"
#include "ImageHandler.hpp"
#include "GaussianBlur.hpp"
#include "ofxBrainWave.h"

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
  
  float getBData(std::string wave);
  ofColor getWaveColor(int n);
  
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
  
  ofxBrainWave mindwave;
  EegData brainData;
  
  std::vector<std::string> waves = { "delta", "theta", "hAlpha", "lAlpha", "hBeta", "lBeta", "hGamma", "lGamma", "attention", "meditation" };
  
  std::map<std::string, float> highs;
  
  std::map<std::string, std::list<float> > graphData;
  
  int previousTime = 0;
  
};
