#include "ofApp.h"


using namespace std;
using namespace cv;
using namespace ct;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0,0,0);
  
  //  ofSetWindowShape(w*2, h);
  //  ofSetWindowPosition(10, 10);
  
  
  ofDisableArbTex();
  
  segmenter = make_unique<Segmentation>();
  img.load("original.jpg");
  img.update();
  layers = segmenter->getSegments(img, 4);
  
  ofTrueTypeFont::setGlobalDpi(72);
  nunitoSans120.load("fonts/Nunito_Sans/NunitoSans-Regular.ttf", 120, true, true);
  
  pigment.allocate(1280, 720, OF_IMAGE_COLOR_ALPHA);
  pigmentCapture.allocate(1280, 720, GL_RGBA);
  pigmentShader.load("shaders/passthrough.vert", "shaders/pigmentShader.frag");

  for (int x = 0; x < 1280; x++) {
    for (int y = 0; y < 720; y++) {
      pigment.setColor(x, y, ofColor(7, 109, 163,0));
    }
  }
  pigment.update();
  
  snapshot = false;
  hideGui = false;
  
  gui.setup();
  gui.add(lowerThreshold.setup("Lower Threshold", 60, 0, 255));
  gui.add(upperThreshold.setup("Upper Threshold", 150, 0, 255));
  gui.add(blurPasses.setup("Blur Passes", 6, 0, 15));
  
  gui.setPosition(w - gui.getWidth(), h - gui.getHeight());
  
  ofAddListener(ofEvents().keyPressed, cameraHandler, &CameraHandler::keyPressed);
  
  printf("Starting Brain Monitor");
  brain = make_unique<Brain>();
  
}

void ofApp::pigmentUpdater() {
  
  ofPixelsRef pix = pigment.getPixels();
  
  for (int x = 0; x < 1280; x++) {
    for (int y = 0; y < 720; y++) {
      
      ofColor c = pix.getColor(x, y);
      
      if (c.a > 0) {
        ofColor cT = pix.getColor(x, y-1);
        ofColor cB = pix.getColor(x, y+1);
        ofColor cL = pix.getColor(x-1, y);
        ofColor cR = pix.getColor(x+1, y);
        
        ofColor nuC = c;
        nuC.a *= .95;
        
        if (cT.a == 0) pix.setColor(x, y-1, nuC);
        if (cB.a == 0) pix.setColor(x, y+1, nuC);
        if (cL.a == 0) pix.setColor(x-1, y, nuC);
        if (cR.a == 0) pix.setColor(x+1, y, nuC);
        
        
      }
      
      c.a *= .95;
      pix.setColor(x, y, c);
    }
  }
  
  pigment.update();
  
  
}

//--------------------------------------------------------------
void ofApp::update(){
  img.update();
  brain->update();
  
  if (countdown != 0) {
    countdown--;
    if (countdown == 0) {
      // do stuff after countdown
    }
  }

//  pigmentUpdater();
  pigment.update();
  
  cameraHandler->update();
  imageHandler.update();
  
  if (cameraHandler->newPhoto()) {
    imageHandler.setOriginal( cameraHandler->getPhoto() );
  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  
  ofSetColor(ofColor::white);
  ofClear(0,0,0,255);
  
//  cameraHandler->draw();
//  imageHandler.draw();
  auto px = pigment.getColor(0, 0);
  
//  ofEnableBlendMode(OF_BLENDMODE_DISABLED);
  
  ofDisableAlphaBlending();
  pigmentCapture.begin();
  ofClear(0,0,0,255);
  pigmentShader.begin();
  pigmentShader.setUniformTexture("tex0", pigment.getTexture(), 0);
//  pigment.draw(0, 0);
  ofDrawRectangle(0, 0, 1280, 720);
  pigmentShader.end();
  pigmentCapture.end();
  
  ofEnableAlphaBlending();
  pigment.draw(0, 0);
//  pigmentCapture.draw(0,0);
  
  
  ofPixels pC;
  pC.allocate(1280, 720, OF_PIXELS_RGBA);
  pigmentCapture.readToPixels(pC);
  pigment.setFromPixels(pC);
//  pigment.draw(0, 0);
  auto px2 = pigment.getColor(0, 0);
  
  brain->drawGraphOverlay();
  
  if (countdown != 0) {
    ofSetColor(ofColor::white);
    ofRectangle bb = nunitoSans120.getStringBoundingBox(to_string(countdown), 0, 0);
    auto h = 1280/2 - bb.getWidth()/2;
    auto v = 720/2 + bb.getHeight()/2;
    nunitoSans120.drawString(to_string(countdown), h, v);
  }
  
  ofSetColor(ofColor::white);
  for (auto &layer : layers) {
    layer->draw(0, 0);
  }
  
  if (!hideGui) {
    gui.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

//  cout << "You Pressed: " << key << endl;
//  109 - m
//  99 - c
  
  int num = key - 48;
  
  if (num >= 0 && num < 10) {
    fN = num;
  }
  
  if (key == 109) {
    snapshot = true;
  }
  
  if (key == 99) {
    snapshot = false;
  }
  
  if (key == 'h') {
    hideGui = !hideGui;
  }
  
  if (key == 'o') {
    imageHandler.resetOriginal();
  }
  
  if (key == ' ') {
    cameraHandler->takePhoto();
  }
  
  if (key == 'r') {
//    countdown = 10;
    // record
//    analyze();
  }
  
  
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

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
