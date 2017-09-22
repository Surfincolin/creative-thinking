#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxGui.h"
#include "CameraHandler.hpp"
#include "ImageHandler.hpp"
#include "GaussianBlur.hpp"
#include "Brain.hpp"
#include "Segmentation.hpp"
#include "WaterColorController.hpp"

class ofApp : public ofBaseApp{
  
  int w = 1280;
  int h = 720;
  
  int fN = 7;
  
  ct::CameraHandler *cameraHandler = new ct::CameraHandler();
  ct::ImageHandler imageHandler;
  
  std::unique_ptr<ct::Brain> brain;
  
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
  
  
    ofImage pic;
    ofImage img;
  
    bool snapshot;
  
    ofTrueTypeFont nunitoSans120;
    int countdown = 0;
  
    unique_ptr<ct::Segmentation> segmenter;
    std::vector<shared_ptr<ofImage>> layers;
  
  ct::WaterColorController *watercolor = new ct::WaterColorController();
  std::shared_ptr<ofFbo> water;
  
};
