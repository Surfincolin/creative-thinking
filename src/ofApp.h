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
  
  
    ofImage pic;
    ofImage img;
  
    bool snapshot;

    ofxBrainWave mindwave;
    EegData brainData;
  
    std::vector<std::string> waves = { "delta", "theta", "hAlpha", "lAlpha", "hBeta", "lBeta", "hGamma", "lGamma", "attention", "meditation" };
    std::map<std::string, float> highs;
    std::map<std::string, std::vector<float> > graphData;
    int previousTime = 0;
  
    ofTrueTypeFont nunitoSans120;
  int countdown = 0;
  void analyze();
  
  ofImage pigment;
  void pigmentUpdater();
  
  ofFbo pigmentCapture;
  ofShader pigmentShader;
  
};
