#include "ofApp.h"


using namespace std;
using namespace cv;
using namespace ct;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(255,255,255,0);
  
  //  ofSetWindowShape(w*2, h);
  //  ofSetWindowPosition(10, 10);
  
  
  ofDisableArbTex();
//  ofSetBackgroundAuto(false);
  ofSetFrameRate(30); // for watercolor
  watercolor->setup();
  
  segmenter = make_unique<Segmentation>();
  img.load("original.jpg");
  img.update();
  layers = segmenter->getSegments(img, 12);
  
  ofTrueTypeFont::setGlobalDpi(72);
  nunitoSans120.load("fonts/Nunito_Sans/NunitoSans-Regular.ttf", 120, true, true);

  snapshot = false;
  hideGui = false;
  
  gui.setup();
  gui.add(lowerThreshold.setup("Lower Threshold", 60, 0, 255));
  gui.add(upperThreshold.setup("Upper Threshold", 150, 0, 255));
  gui.add(blurPasses.setup("Blur Passes", 6, 0, 15));
  
  gui.setPosition(w - gui.getWidth(), h - gui.getHeight());
  
  ofAddListener(ofEvents().keyPressed, cameraHandler, &CameraHandler::keyPressed);
  
  printf("Starting Brain Monitor\n");
  brain = make_unique<Brain>();
  
//  brush.load("brush.png");
//  test.allocate(1280, 720);
//  test.begin();
//  ofClear(0, 0, 0, 255);
//  test.end();
  
}

//--------------------------------------------------------------
void ofApp::update(){
  img.update();
  brain->update();
  watercolor->update();
  
  if (countdown != 0) {
    countdown--;
    if (countdown == 0) {
      // do stuff after countdown
    }
  }

  
  cameraHandler->update();
  imageHandler.update();
  
  if (cameraHandler->newPhoto()) {
    imageHandler.setOriginal( cameraHandler->getPhoto() );
  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  
//  ofSetColor(ofColor::white);
//  ofClear(0,0,0,255);
//  
////  cameraHandler->draw();
////  imageHandler.draw();  
//  
//  brain->drawGraphOverlay();
//  
//  if (countdown != 0) {
//    ofSetColor(ofColor::white);
//    ofRectangle bb = nunitoSans120.getStringBoundingBox(to_string(countdown), 0, 0);
//    auto h = 1280/2 - bb.getWidth()/2;
//    auto v = 720/2 + bb.getHeight()/2;
//    nunitoSans120.drawString(to_string(countdown), h, v);
//  }
//  
//  ofSetColor(ofColor::white);
////  for (auto &layer : layers) {
////    layer->draw(0, 0);
////  }
//
//  ofSetColor(255,255,255,255);
  
  watercolor->draw();
//
//  if (!hideGui) {
//    gui.draw();
//  }
//  ofClear(0, 0, 0,255);
//  glEnable(GL_BLEND);
////  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
////  glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
//  test.begin();
//  
//  brush.draw(640, 360);
//  test.end();
////  glBlendFunc(GL_ZERO, GL_SRC_COLOR);
//  test.draw(0,0);
////  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  //  glBlendFunc(GL_ZERO, GL_SRC_COLOR);
//  //  bg.draw(0,0);
//  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  brush.draw(0,0);
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
  
  if (key == 'a') {
    watercolor->pressed = true;
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
  watercolor->mPressed();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  watercolor->mReleased();
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
