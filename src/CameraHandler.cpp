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
  
//  photo.init();
  bCamIsBusy = false;
  original = make_shared<ofImage>();
  original->allocate(1280,720, OF_IMAGE_COLOR);

//  photo.test();
}

void CameraHandler::takePhoto() {
  
  busy = true;
//  photo.startCapture();
  photo.init();
  
}


shared_ptr<ofImage> CameraHandler::getPhoto() {
  
  newImage = false;
  return original;
  
}

void CameraHandler::update() {
  
  if (photo.captureSucceeded()) {
    printf("Trying to load data...\n");
    pic = photo.capture();
    original->setFromPixels(pic, photo.getCaptureWidth(), photo.getCaptureHeight(), OF_IMAGE_COLOR,0);
    
    // Weird Color Fix
    ofPixels pix = original->getPixels();
    original->setFromPixels(pix);
    
    printf("Loading finished!\n");
    busy = false;
    newImage = true;
  }
  
}

void CameraHandler::draw() {
  
//  ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", 20, 20);
//  ofDrawBitmapString("Press 't' to take a photo", 20, 35);
}


void CameraHandler::keyPressed(ofKeyEventArgs& eventArgs) {
//  cout << "a key was pressed" << endl;
//  if (eventArgs.key == 't') {
//    if (!photo.isBusy()) {
//      photo.startCapture();
//    } else {
//      printf("Cam is busy.\n");
//    }
//  }
//  
//  if (eventArgs.key == 'e') {
//    printf("Closing Camera.\n");
//    photo.exit();
//  }
}

CameraHandler::~CameraHandler() {
  printf("CameraHandler Exiting.\n");
  photo.exit();
};
