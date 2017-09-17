#include "ofApp.h"


using namespace std;
using namespace cv;
using namespace ct;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0,0,0);
  
  
  //  ofSetWindowShape(w*2, h);
  //  ofSetWindowPosition(10, 10);
  
  //gBlur = make_shared<ct::GaussianBlur>(w,h);
  
  
  ofDisableArbTex();
  chromaticShader.load("shaders/passthrough.vert", "shaders/chromaticShader.frag");
  colorDodge.load("shaders/passthrough.vert", "shaders/colorDodge.frag");
  findEdge.load("shaders/passthrough.vert", "shaders/findEdge.frag");
//  blurX.load("shaders/blurX");
//  blurY.load("shaders/blurY");
  
  snapshot = false;
  hideGui = false;
  
  gui.setup();
  gui.add(lowerThreshold.setup("Lower Threshold", 60, 0, 255));
  gui.add(upperThreshold.setup("Upper Threshold", 150, 0, 255));
  gui.add(blurPasses.setup("Blur Passes", 6, 0, 15));
  
  gui.setPosition(w*2 - gui.getWidth(), h - gui.getHeight());
  
//  ofAddListener(ofEvents().keyPressed, cameraHandler, &CameraHandler::keyPressed);
  ofAddListener(ofEvents().keyPressed, cameraHandler, &CameraHandler::keyPressed);
  
//  cam.setup(w, h);
//  img.load("img.jpg");
  
  
//  colorImg.allocate(w, h);
//  grey.allocate(w, h);
//  canny.allocate(w, h);
//  hsb.allocate(w,h);
//  invertedGrey.allocate(w,h);
  
//  edgePassFbo.allocate(w, h);
//  fboPassTwo.allocate(w, h);
//  fboDodge.allocate(w, h);


//  faces.setup("haarcascade_frontalface_alt.xml");
  
//  plane.set(w, h, 10, 10);
//  plane.mapTexCoords(0, 480.0, 640.0, 0);
  //  plane.mapTexCoordsFromTexture(img.getTexture());
  
  for (auto w : waves) {
    highs.insert(make_pair(w, 0));
    graphData.insert(make_pair(w, list<float>() ));
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

//--------------------------------------------------------------
void ofApp::update(){
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
      
      graphData.at(w).pop_front();
      graphData.at(w).push_back(rel);
    }
    
    previousTime = currentTime;
  }
  
  cameraHandler->update();
  imageHandler.update();
  
  if (cameraHandler->newPhoto()) {
    imageHandler.setOriginal( cameraHandler->getPhoto() );
  }
  
//  cam.update();
  
//  if (cam.isFrameNew()) {
  
    // copy webcam pixels
//    colorImg.setFromPixels(cam.getPixels());
//    
//    // mirror horizontally
//    colorImg.mirror(false, true);
//    
//    // convert to hsb
//    hsb = colorImg;
//    hsb.convertRgbToHsv();
//    
//    // create grey scale version
//    hsb.convertToGrayscalePlanarImage(grey, 2);
    

//    cvCanny(colorImg.getCvImage(), canny.getCvImage(), lowerThreshold, upperThreshold);
//    canny.flagImageChanged();
    
//    faces.findHaarObjects(colorImg.getPixels());
    
    
    
//  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(ofColor::white);
  
  cameraHandler->draw();
  imageHandler.draw();
  
  
//  float opacity = ofMap(mouseX, 0, ofGetWidth(), 0.0, 1.0, true);
////  float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 1.0, true);
//  float alpha = ofMap(mouseX, 0, ofGetWidth(), 0.0, 2.0, true);
//  float beta = ofMap(mouseY, 0, ofGetHeight(), -100.0/255.0, 100.0/255.0, true);
//  
//  
//  edgePassFbo.begin();
//  ofClear(255);
//  findEdge.begin();
//  findEdge.setUniform2f("resolution", w, h);
//  cam.draw(0, 0, w, h);
//  findEdge.end();
//  edgePassFbo.end();
//
//  auto blurred = gBlur->blurImage(cam, blurPasses);
//  blurred->mirror(true, true);
//
//  fboDodge.begin();
//  ofClear(255);
//  colorDodge.begin();
//  colorDodge.setUniformTexture("image", grey.getTexture(), 1);
//  colorDodge.setUniformTexture("edges", edgePassFbo.getTexture(), 2);
//  colorDodge.setUniform1f("opacity", opacity);
//  colorDodge.setUniform1i("fN", fN);
//  colorDodge.setUniform1f("alpha", alpha);
//  colorDodge.setUniform1f("beta", beta);
//  blurred->draw(0,0);
//  colorDodge.end();
//  fboDodge.end();
//
//  grey.draw(0,0);
//
//  fboDodge.draw(0,0);
  
  
  
  
  ofSetLineWidth(5);
//  ofSetHexColor(0xFF0000);
  
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

//  ofDrawLine(20, 720/2, 1200, 720/5);
  
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
    pic = canny.getPixels();
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
//    cameraHandler->standbyForPhoto();
  }
  
  if (key == ' ') {
//    imageHandler.setOriginal( cameraHandler->takePhoto() );
    cameraHandler->takePhoto();
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
