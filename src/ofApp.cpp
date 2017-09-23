#include "ofApp.h"


using namespace std;
using namespace cv;
using namespace ct;

//--------------------------------------------------------------
void ofApp::setup(){
  ofDisableArbTex();
  ofSetFrameRate(30); // for watercolor
  ofBackground(255,255,255,0);
  
  //  ofSetWindowShape(w*2, h);
  //  ofSetWindowPosition(10, 10);
  
  watercolor->setup();
  
  ofTrueTypeFont::setGlobalDpi(72);
  nunitoSans120.load("fonts/Nunito_Sans/NunitoSans-Regular.ttf", 120, true, true);
  
  ofAddListener(ofEvents().keyPressed, cameraHandler, &CameraHandler::keyPressed);
  
  brain = make_unique<Brain>();
  
  background = imageHandler.getProcessedImage();
  brush.load("brush.png");
  
  int i = 0;
  for (auto &w : brain->waves) {
    previousValues.insert(make_pair(w, 0.0));
    brushPositions.push_back(ofVec2f(0));
    ofColor c = getNextColor(i);
    watercolor->addColor(c);
    i++;
  }
  

}

void ofApp::nextState() {
  state = (state == 7) ? 0 : state + 1;
}

//--------------------------------------------------------------
ofColor ofApp::getNextColor(int n) {
  
  float phase = 0;
  float freq = PI*2/brain->waves.size();
  int center = 128;
  int width = 127;
  
  int r = sin(freq * n + 2 + phase) * width + center;
  int g = sin(freq * n + 0 + phase) * width + center;
  int b = sin(freq * n + 4 + phase) * width + center;
  
  return ofColor(r, g, b);
}

void ofApp::serviceStarter() {
  
  if (state == RESTART) {
  }
  
  if (state == TAKE_PHOTO) {
    background->clear();
    cameraHandler->takePhoto();
  }
  
  if (state == BRAIN_DATA) {
    brain->resetHighs();
    paintWater = true;
    enough = drawFrames;
  }
  
}

//--------------------------------------------------------------
void ofApp::update(){

  brain->update();
  
  int currentTime = ofGetFrameNum() / 30; //60fps
  if (currentTime > previousTime) {
    
    if (countdown != 0) {
      countdown--;
      if (countdown == 0) {
        // do stuff after countdown
        nextState();
      }
    }
    previousTime = currentTime;
  }
  
  cameraHandler->update();
  
  if (cameraHandler->newPhoto()) {
    imageHandler.setOriginal( cameraHandler->getPhoto() );
    nextState();
  }
  
  if (state == BRAIN_DATA || state == INSTRUCTION_3) {
    watercolor->update();
  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofClear(0, 0, 0, 255);
  ofSetColor(255, 255, 255);
  
  
  if (state == RESTART) {
    ofDrawBitmapString("Please wait resetting...", 20, 35);
  }
  
  if (state == READY) {
    ofDrawBitmapString("READY!! Press 'space' to begin.", 20, 35);
  }
  
  if (state == INSTRUCTION_1) {
    ofDrawBitmapString("Lets take a photo, press the button and smile.", 20, 35);
  }
  
  if (state == TAKE_PHOTO) {
      
    ofDrawBitmapString("Smile!!!", 20, 35);
  }

  if (state == INSTRUCTION_2) {
      
//      imageHandler.draw();
    
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, 1280, 720);
    background->draw(0, 0);
    
    brain->drawGraphOverlay();
    
    ofDrawBitmapString("Alright put on the brain device. 'space' to continue.", 20, 35);
  }
  
  if (state == BRAIN_DATA) {
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, 1280, 720);
    background->draw(0, 0);
//    if (enough > 0) {
//      printf("p");
      paintBrainData();
//    }

//    ofBlendMode(OF_BLENDMODE_SCREEN);
//    background->draw(0, 0);
//    
    water = watercolor->draw();
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    water->draw(0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Try and think of some fond memories.", 20, 35);
  }
  
  if (state == INSTRUCTION_3) {
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, 1280, 720);
    background->draw(0, 0);
    
    water = watercolor->draw();
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    water->draw(0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Great! This is your mind selfie!", 20, 35);
  }
  
  if (state == FINALIZE) {

    ofDrawBitmapString("Saving...", 20, 35);
  }
  
}

void ofApp::paintBrainData() {
  
  
  int hz = ofGetWidth() * 0.8;
  int vr = ofGetHeight() * 0.5;
  int side = ofGetWidth() * 0.2 / 2;
  int top = ofGetHeight() * 0.1 / 2;
  
  int i = 0;
  for (auto &w : brain->waves) {
    int counter = 0;
    float width = 120 * brain->latestData->at(w);
    float currentWidth = width;
    ofVec2f pos = {side+ofRandom(hz) , top+ofRandom(vr)};
    ofVec2f target = ofVec2f(0);
    target.x = pos.x + (ofRandom(128) - 64.0);
    target.y = pos.y + (ofRandom(128) - 64.0);
    ofVec2f vec = ofVec2f(0,0);
    
    float len = pos.distance(target);
    
    float p = max((float)(enough / drawFrames), 0.0f);
//    float p2 = max((float)(enough+150 / drawFrames), 0.0f);
    
    while (counter < 1000) {
      counter++;
      currentWidth = min(width, max(width / 4.f, currentWidth - (len - 25) * 0.001f));
      
      vec += (target - pos).normalize() * 0.03;
      vec *= 0.97;
      if (vec.length() > 2) {
        vec = vec.normalize() * 2;
      }
      
      pos += vec;
      
      watercolor->canvas.beginWaterDraw();
      ofPushStyle();
      ofSetColor(70, ofRandom(100, 120), 0, 300 / currentWidth * p);
      brush.draw(pos.x - currentWidth * 1.05 / 2 * 2, pos.y - currentWidth * 1.05/ 2 * 2, currentWidth * 1.05 * 2, currentWidth * 1.05 * 2);
      ofPopStyle();
      watercolor->canvas.endWaterDraw();
      
      watercolor->canvas.beginPigmentDraw(i);
      ofPushStyle();
      ofSetColor(ofRandom(100, 150), 0, 0, 300 / currentWidth / 2 * p*1.5);
      brush.draw(pos.x - currentWidth / 2 * 2, pos.y - currentWidth / 2 * 2, currentWidth * 2, currentWidth * 2);
      ofPopStyle();
      watercolor->canvas.endPigmentDraw();
      
      if (pos.distance(target) < 10) {break;}
      
    }
    
    i++;
    enough--;
  }
  
//  brain->drawGraphOverlay();
  
  if (countdown != 0) {
    ofSetColor(ofColor::white);
    ofRectangle bb = nunitoSans120.getStringBoundingBox(to_string(countdown), 0, 0);
    auto h = 1280/2 - bb.getWidth()/2;
    auto v = 720/2 + bb.getHeight()/2;
    nunitoSans120.drawString(to_string(countdown), h, v);
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
//    cameraHandler->takePhoto();
//    state++;
    nextState();
    serviceStarter();
  }
  if (key == 'b') {
//    begin();
  }
  
  if (key == 'r') {
    countdown = 10;
    // record
//    analyze();
  }
  
  if (key == 'a') {
    watercolor->pressed = true;
  }
  
  if (key == 'x') {
    brain->resetHighs();
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
