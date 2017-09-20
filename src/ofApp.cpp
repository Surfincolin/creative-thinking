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
  
  img.load("original.jpg");
  img.update();
  segmenter = make_unique<Segmentation>();
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
  
  for (auto w : waves) {
    highs.insert(make_pair(w, 0));
    graphData.insert(make_pair(w, vector<float>() ));
  }
  
  for (int i = 0; i < 50; i++) {
    for (auto w : waves) {
      graphData.at(w).push_back(0.0);
    }
  }
  
  mindwave.setup();
  mindwave.start();
}

float ofApp::getBData(std::string wave) {
  float val = 0.0;
  
  if (wave == "delta") val =	brainData.delta;
  if (wave == "theta") val =	brainData.theta;
  if (wave == "hAlpha") val =	brainData.highAlpha;
  if (wave == "lAlpha") val =	brainData.lowAlpha;
  if (wave == "hBeta") val =	brainData.highBeta;
  if (wave == "lBeta") val =	brainData.lowBeta;
  if (wave == "hGamma") val =	brainData.highGamma;
  if (wave == "lGamma") val =	brainData.lowGamma;
  if (wave == "attention") val =	brainData.attention;
  if (wave == "meditation") val =	brainData.meditation;
  
  return val;
  
}

ofColor ofApp::getWaveColor(int n) {
  
  float phase = 0;
  float freq = PI*2/waves.size();
  int center = 128;
  int width = 127;
  
  int r = sin(freq * n + 2 + phase) * width + center;
  int g = sin(freq * n + 0 + phase) * width + center;
  int b = sin(freq * n + 4 + phase) * width + center;

  return ofColor(r, g, b);
}

void ofApp::analyze() {
  printf("Analyzing!");
  
  vector<float> &ref = graphData.at("theta");
  int crop = min((int)ref.size(), 10);
  
  vector<float> tempData(ref.end() - crop, ref.end() );
  
  ofPixelsRef pix = pigment.getPixels();
  
  for (auto val : tempData) {
    val = ofRandom(720.0);
    printf("theta: %f\n", val);
    
    float x = ofRandom(1280.0);
    float y = ofRandom(720.0);
    
    pix.setColor(x, y, ofColor(7, 109, 163, 255));
    
  }
  
  pigment.update();
  
//  7, 109, 163
  
  
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
  brainData = mindwave.getEegData();
  
  for (auto w : waves) {
    auto v = getBData(w);
    auto n = highs.at(w);
    highs.at(w) = (v > n) ? v : n;
  }
  
  int currentTime = ofGetFrameNum() / 60;
  if (currentTime > previousTime) {
  
    for (auto w : waves) {
      
      float rel = ofMap(getBData(w), 0.0, highs.at(w), 0.0, 720.0);
      
      graphData.at(w).erase(graphData.at(w).begin());
      graphData.at(w).push_back(rel);
    }
    
    // handle countdown
    if (countdown != 0) {
      countdown--;
      if (countdown == 0) {
        analyze();
      }
    }
    
    previousTime = currentTime;
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
//  ofSetBackgroundColor(255, 0, 0);
  
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
  
//  printf("PX:: r: %i, g: %i, b: %i, a: %i\n", px.r, px.g, px.b, px.a);
//  printf("PX2:: r: %i, g: %i, b: %i, a: %i\n", px2.r, px2.g, px2.b, px2.a);
  
  ofSetLineWidth(5);
  
  float div = 1280/50;
  float cN = 0;
  for (auto w : waves) {
    ofColor color = getWaveColor(cN);
    ofSetColor(color);
    
    ofVec2f prev(0.0,0.0);
    int i = 0;
    for (auto p : graphData.at(w)) {
      float x = div * (float)i;
      if (i != 0) {
        ofDrawLine(prev.x, 720.0-prev.y, x, 720.0-p);
      }
      prev.x = x;
      prev.y = p;
      i++;
    }
    cN++;
  }
  
  ofSetHexColor(0xFFFFFF);

  ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", 20, 20);
  ofDrawBitmapString("Press 'space' to take a photo", 20, 35);

  
  ofDrawBitmapString("BRAIN DATA", 20, 720-180);
  cN = 0;
  for (auto w : waves) {
    ofColor color = getWaveColor(cN);
    ofSetColor(color);
    ofDrawBitmapString(w + ": " + to_string((int)getBData(w)) + " ", 20, 720 - 165 + (15*cN));
    cN++;
  }
  
  
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
    analyze();
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
