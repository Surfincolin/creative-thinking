//
//  CameraHandler.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#include "CameraHandler.hpp"

using namespace ct;

CameraHandler::CameraHandler() {
  
  cam.setup(ofGetWidth(), ofGetHeight());
  camWidth = cam.getWidth();
  camHeight = cam.getHeight();
  picSave.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
  //cam.close();
  
}

void CameraHandler::standbyForPhoto() {
  
  cam.setup(camWidth, camHeight);
  active = true;
  
}


ofImage CameraHandler::takePhoto() {
  
  if (active) {
    picSave = cam.getPixels();

    active = false;
    cam.close();
  } else {
    cout << "The Camera isn't ready to take a photo." << endl;
  }
  
  return picSave;
  
}

void CameraHandler::update() {
  if (active) cam.update();
  
}

void CameraHandler::draw() {
  if (active) cam.draw(camWidth, 0.0, -camWidth, camHeight);
}


CameraHandler::~CameraHandler() {};
