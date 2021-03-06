//
//  WaterColorController.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//

#include "WaterColorController.hpp"

using namespace ct;

WaterColorController::WaterColorController() {
  
}

//--------------------------------------------------------------
void WaterColorController::setup() {
  ofSetLogLevel(OF_LOG_ERROR);
  
  bg.load("bg_white.png");
  brush.load("brush.png");
  pressed = false;
  
//  addColor(ofColor(7, 109,163, 255));
//  addColor(ofColor(247,58,108, 255));
//  addColor(ofColor(15,145,92, 255));
//  addColor(ofColor(189, 99, 215, 255));
  
  state = STATE_MIX;
  currentPigment = 0;
  width = 120;
  
}

//--------------------------------------------------------------
void WaterColorController::addColor(ofColor iColor) {
  canvas.addPigment(iColor);
  colorCount++;
  
  printf("Color Added, count: %i\n", colorCount);
}

//--------------------------------------------------------------
void WaterColorController::addColorLayer(shared_ptr<ofImage> iImage, ofColor iColor) {
  imageLayers.push_back(iImage);
  canvas.addPigment(iColor);
  colorCount++;
}

//--------------------------------------------------------------
void WaterColorController::resetColors() {
  canvas.clearPigments();
  colorCount = 0;
  currentPigment = 0;
}

//--------------------------------------------------------------
void WaterColorController::update(){
  
    if (pressed) {strokeDraw();}
//  if (pressed) { imageLayerDraw(); }
  
  canvas.update();
}

//--------------------------------------------------------------
shared_ptr<ofFbo> WaterColorController::draw(){

  
  return canvas.draw();

//  glBlendFunc(GL_ZERO, GL_SRC_COLOR);
//  bg.draw(0,0);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  
//  string str;
//  if (state == STATE_WATER) { str = "water"; }
//  if (state == STATE_PIGMENT) { str = "pigment"; }
//  if (state == STATE_MIX) { str = "mix"; }
//  str += "  width: " + ofToString(width) + "  pigment: " + ofToString(currentPigment);
//  ofDrawBitmapString(str, 20, 20);
}

//--------------------------------------------------------------
void WaterColorController::strokeDraw() {
  int counter = 0;
  ofPoint target = ofPoint(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
  float len = pos.distance(target);
  
  while (counter < 1000) {
    counter ++;
    currentWidth = min(width, max(width / 4.f, currentWidth - (len - 25) * 0.001f));
    
    vec += (target - pos).normalize() * 0.03;
    vec *= 0.97;
    if (vec.length() > 2) {
      vec = vec.normalize() * 2;
    }
    
    pos += vec;
    
    if (state == STATE_WATER || state == STATE_MIX) {
      canvas.beginWaterDraw();
      ofPushStyle();
      ofSetColor(128, ofRandom(100, 120), 0, 300 / currentWidth);
      brush.draw(pos.x - currentWidth * 1.05 / 2 * 2, pos.y - currentWidth * 1.05/ 2 * 2, currentWidth * 1.05 * 2, currentWidth * 1.05 * 2);
      ofPopStyle();
      canvas.endWaterDraw();
    }
    
    
    if (state == STATE_PIGMENT || state == STATE_MIX) {
      canvas.beginPigmentDraw(currentPigment);
      ofPushStyle();
      ofSetColor(ofRandom(100, 150), 0, 0, 300 / currentWidth / ((state == 2) ? 2 : 1));
      brush.draw(pos.x - currentWidth / 2 * 2, pos.y - currentWidth / 2 * 2, currentWidth * 2, currentWidth * 2);
      
      ofPopStyle();
      canvas.endPigmentDraw();
    }
    
    if (pos.distance(target) < 10) {break;}
  }
}

//--------------------------------------------------------------
void WaterColorController::imageLayerDraw() {
  int counter = 0;
//  ofPoint target = ofPoint(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
//  float len = pos.distance(target);
  
//  while (counter < 1000) {
    counter ++;
//    currentWidth = min(width, max(width / 4.f, currentWidth - (len - 25) * 0.001f));
    
//    vec += (target - pos).normalize() * 0.03;
//    vec *= 0.97;
//    if (vec.length() > 2) {
//      vec = vec.normalize() * 2;
//    }
    
//    pos += vec;
  if (waterbrush % 2 == 0) {
    printf("water\n");
    if (state == STATE_WATER || state == STATE_MIX) {
      canvas.beginWaterDraw();
      ofPushStyle();
      ofSetColor(128, ofRandom(100, 120), 0, 300 / currentWidth);
      //        brush.draw(pos.x - currentWidth * 1.05 / 2 * 2, pos.y - currentWidth * 1.05/ 2 * 2, currentWidth * 1.05 * 2, currentWidth * 1.05 * 2);
      ofClear(127, 127, 127);
      //        cImage->draw(0, 0);
      ofPopStyle();
      canvas.endWaterDraw();
    }
    
  } else {
  
      for (auto &cImage : imageLayers) {
        
        if (state == STATE_PIGMENT || state == STATE_MIX) {
          canvas.beginPigmentDraw(currentPigment);
          ofPushStyle();
          ofSetColor(ofRandom(100, 150), 0, 0, 300 / currentWidth / ((state == 2) ? 2 : 1));
  //        brush.draw(pos.x - currentWidth / 2 * 2, pos.y - currentWidth / 2 * 2, currentWidth * 2, currentWidth * 2);
          cImage->draw(0, 0);
          ofPopStyle();
          canvas.endPigmentDraw();
        }
        //switch color
        currentPigment = (currentPigment + 1) % 4;
      }
  }
  
  
//    if (pos.distance(target) < 10) {break;}
//  }
}


void WaterColorController::mPressed () {
  pressed = true;
  pos.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
  vec.set(0,0);
  currentWidth = width;
}

void WaterColorController::mReleased () {
  pressed = false;
  waterbrush++;
//  currentPigment = (currentPigment + 1) % 4;
}
