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
  ofSetFrameRate(30); // for watercolor
  watercolor->setup();
  
  segmenter = make_unique<Segmentation>();

  
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
  
  background = imageHandler.getProcessedImage();
  
  brush.load("brush.png");
  
  int i = 0;
  for (auto &w : brain->waves) {
    printf("wave: %s\n", w.c_str());
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

void ofApp::begin() {
  
//  img.load("test-photo.jpg");
//  img.update();
  
  ofImage temp = ofImage(cameraHandler->getPhoto()->getPixels());
  
  auto wid = temp.getWidth();
  auto hig = temp.getHeight();
  
  int nHi = wid * 720.0/1280.0;
  int buffer = (hig - nHi) / 2.0;
  
  temp.crop(0, buffer, wid, nHi);
  temp.resize(1280, 720);
  
  layers = segmenter->getSegments(temp, 8);
  
  // add segments to watercolor
  for (int i = 0; i < layers.size(); i++) {
    ofColor lColor = getNextColor(i);
    watercolor->addColorLayer(layers.at(i), lColor);
  }
  
  printf("begin finished\n");
  
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

void ofApp::countDown() {
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
}

void ofApp::serviceStarter() {
  
  if (state == RESTART) {
  }

//    case StateController::READY :

//    case StateController::INSTRUCTION_1 :
  
  if (state == TAKE_PHOTO) {
    background->clear();
    cameraHandler->takePhoto();
  }
  
//    case StateController::INSTRUCTION_2 :
  
  if (state == BRAIN_DATA) {
    brain->resetHighs();
    paintWater = true;
  }
  
//    case StateController::INSTRUCTION_3 :
  
//    case StateController::FINALIZE :
  
}

//--------------------------------------------------------------
void ofApp::update(){

  background->update();
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
  
  if (state == BRAIN_DATA) {
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
//    background->draw(0, 0);
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, 1280, 720);
    
    brain->drawGraphOverlay();
    
    ofDrawBitmapString("Alright put on the brain device. 'space' to continue.", 20, 35);
  }
  
  if (state == BRAIN_DATA) {
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 0, 1280, 720);
    
    paintBrainData();
//
//    ofBlendMode(OF_BLENDMODE_SCREEN);
//    //      imageHandler.draw();
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
      
    
    
    ofDrawBitmapString("Great! This is your mind selfie!", 20, 35);
  }
  
  if (state == FINALIZE) {

    ofDrawBitmapString("Saving...", 20, 35);
  }
  
  
//  ofSetColor(ofColor::white);
//  for (auto &layer : layers) {
//    layer->draw(0, 0);
//  }
  
//  if (!hideGui) {
//    gui.draw();
//  }
}

void ofApp::paintBrainData() {
  int currentWidth = 120;
//  ofRandomuf()
  int hz = ofGetWidth() * 0.8;
  int vr = ofGetHeight() * 0.5;
  int side = ofGetWidth() * 0.2 / 2;
  int top = ofGetHeight() * 0.1 / 2;
  
//  if (paintWater) {
//    int x = ofRandom(hz);
//    int y = ofRandom(vr);
//    
//    brushPositions.at(0) = ofVec2f(x, y);
//  } else {
//    brushPositions.at(0).x += (ofRandom(12) - 6.0);
//    brushPositions.at(0).y += (ofRandom(12) - 6.0);
//  }
  
  int i = 0;
  for (auto &w : brain->waves) {
    if (previousValues.at(w) == brain->latestData->at(w)) {
      previousValues.at(w) = brain->latestData->at(w);
      int x = ofRandom(hz);
      int y = ofRandom(vr);

      brushPositions.at(i) = ofVec2f(x, y);
      
    } else {
      brushPositions.at(i).x += (ofRandom(24) - 12.0);
      brushPositions.at(i).y += (ofRandom(24) - 12.0);
    }
    i++;
  }
  
//  printf("mid paint Brain...");
  
  if (paintWater) {
    watercolor->canvas.beginWaterDraw();
    ofPushStyle();
    ofSetColor(128, ofRandom(100, 120), 0, 300 / currentWidth);
    ofClear(70, 70, 70);
    ofPopStyle();
    watercolor->canvas.endWaterDraw();
    paintWater = false;
  }
  
  i = 0;
  for (auto &w: brain->waves) {
    watercolor->canvas.beginPigmentDraw(i);
    ofPushStyle();
    ofSetColor(ofRandom(100, 150), 0, 0, 300 / currentWidth / ((watercolor->state == 2) ? 2 : 1));
    //brush draw
    ofVec2f pos = brushPositions.at(i);
    brush.draw(pos.x - currentWidth / 2 * 2, pos.y - currentWidth / 2 * 2, currentWidth * 2, currentWidth * 2);
//    brush.draw(brushPositions.at(0));
    ofPopStyle();
    watercolor->canvas.endPigmentDraw();
    i++;
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
    begin();
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
