#include "ofApp.h"


using namespace std;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0,0,0);
  
  //  ofSetWindowShape(w*2, h);
  //  ofSetWindowPosition(10, 10);
  
  gBlur = make_shared<ct::GaussianBlur>(w,h);
  
  
  ofDisableArbTex();
  chromaticShader.load("shaders/chromaticShader");
  colorDodge.load("shaders/colorDodge");
//  blurX.load("shaders/blurX");
//  blurY.load("shaders/blurY");
  
  snapshot = false;
  hideGui = false;
  
  gui.setup();
  gui.add(lowerThreshold.setup("Lower Threshold", 60, 0, 255));
  gui.add(upperThreshold.setup("Upper Threshold", 150, 0, 255));
  gui.add(blurPasses.setup("Blur Passes", 6, 0, 15));
  
  gui.setPosition(w*2 - gui.getWidth(), h - gui.getHeight());
  
  cam.setup(w, h);
//  img.load("img.jpg");
  
  
  colorImg.allocate(w, h);
  grey.allocate(w, h);
  canny.allocate(w, h);
  hsb.allocate(w,h);
  invertedGrey.allocate(w,h);
  
//  fboPassOne.allocate(w, h);
//  fboPassTwo.allocate(w, h);
  fboDodge.allocate(w, h);


//  faces.setup("haarcascade_frontalface_alt.xml");
  
  plane.set(w, h, 10, 10);
  plane.mapTexCoords(0, 480.0, 640.0, 0);
  //  plane.mapTexCoordsFromTexture(img.getTexture());
}

//--------------------------------------------------------------
void ofApp::update(){
  cam.update();
  
  if (cam.isFrameNew()) {
    
    // copy webcam pixels
    colorImg.setFromPixels(cam.getPixels());
    
    // mirror horizontally
    colorImg.mirror(false, true);
    
    // convert to hsb
    hsb = colorImg;
    hsb.convertRgbToHsv();
    
//     create grey scale version
    hsb.convertToGrayscalePlanarImage(grey, 2);
    
//    invertedGrey = grey;
//    invertedGrey.invert();
    
//    cvCanny(colorImg.getCvImage(), canny.getCvImage(), lowerThreshold, upperThreshold);
//    canny.flagImageChanged();
    
//    faces.findHaarObjects(colorImg.getPixels());
    
    
    
  }

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(ofColor::white);
  
//  float blur = ofMap(mouseX, 0, ofGetWidth(), 0, 1.0, true);
  float alpha = ofMap(mouseX, 0, ofGetWidth(), 0.0, 2.0, true);
  float beta = ofMap(mouseY, 0, ofGetHeight(), -100.0/255.0, 100.0/255.0, true);
  
  //draw all cv images
//  colorImg.draw(0,0);
//  ofImage test = colorImg.getPixels();
//  test.getTextureReference().bind();
  
//  img.getTexture().bind();
  
//  fboPassOne.begin();
//  blurX.begin();
//  invertedGrey.draw(0,0);
//  blurX.end();
//  fboPassOne.end();
//  
//
//  fboPassTwo.begin();
//  blurY.begin();
//  fboPassOne.draw(0,0);
//  blurY.end();
//  fboPassTwo.end();
//  
//  for (int i = 0; i < 6; i++) {
//    
//    fboPassOne.begin();
//    blurX.begin();
//    fboPassTwo.draw(0,0);
//    blurX.end();
//    fboPassOne.end();
//    
//    
//    fboPassTwo.begin();
//    blurY.begin();
//    fboPassOne.draw(0,0);
//    blurY.end();
//    fboPassTwo.end();
//    
//  }
//  
//    ofPushMatrix();
//    ofTranslate(ofGetWidth()*0.5, 0);
//    fboPassTwo.draw(0,0);
//    ofPopMatrix();
  
  
//  cam.draw(0,0);
  auto blurred = gBlur->blurImage(cam, blurPasses);
  blurred->mirror(true, true);
//  blurred->draw(0, 0);
  
  
//  blurred.draw(0, 0);
//
  fboDodge.begin();
  colorDodge.begin();
  colorDodge.setUniformTexture("image", grey.getTexture(), 1);
  colorDodge.setUniform1i("fN", fN);
  colorDodge.setUniform1f("alpha", alpha);
  colorDodge.setUniform1f("beta", beta);
  blurred->draw(0,0);
////  grey.draw(0,0);
  colorDodge.end();
  fboDodge.end();
//
  grey.draw(0,0);
  fboDodge.draw(0,0);
  

//  if (snapshot) {
//    pic.draw(w, 0);
//  } else {
//    canny.draw(w, 0);
//  }

//  ofSetColor(0,255,0);
//  ofNoFill();
//  ofSetLineWidth(2);
//  for (int i = 0; i < faces.blobs.size(); i++) {
//    ofDrawRectangle(faces.blobs[i].boundingRect);
//  }
  
//  cam.getTexture().bind();
//  
//  // Shader Work
////  ofSetColor(255);
//  chromaticShader.begin();
//  chromaticShader.setUniform1f("time", ofGetElapsedTimef()/1000.0);
//  chromaticShader.setUniform2f("resolution", ofVec2f(w, h));
//  
////  ofDrawRectangle(0, 0, ofGetWidth()/2, ofGetHeight());
//  ofPushMatrix();
////  ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//  ofTranslate(ofGetWidth()/4, ofGetHeight()/2);
//  plane.draw();
//  ofPopMatrix();
//  
////  colorImg.draw(0, 0);
////  cam.draw(0, 0, 640, 480);
//  chromaticShader.end();
//  
//  cam.getTexture().unbind();
////  test.getTextureReference().unbind();
////  img.getTexture().unbind();
//
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
