//
//  ImageHandler.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#include "ImageHandler.hpp"

using namespace ct;

ImageHandler::ImageHandler() {
  
  processedImage = make_shared<ofImage>();
  processedImage->allocate(1280, 720, OF_IMAGE_COLOR);
  
}

void ImageHandler::setOriginal(shared_ptr<ofImage> iPic) {
  printf("setOriginal\n");
//  originalImage->clear();
  originalImage = iPic;
  
  fx.setup(iPic->getWidth(), iPic->getHeight());
//  fx.setup(1280, 720);
  fx.turnOnEffect(EFFECTS::BLUR);
  fx.turnOnEffect(EFFECTS::FINDEDGE);
  fx.turnOnEffect(EFFECTS::BLENDER);

//  originalImage.clone(iPic);
  processImage();
  active = true;
}

void ImageHandler::resetOriginal() {
  active = false;
//  originalImage.clear();
}

void ImageHandler::update() {
//  if (active) {
//    
//    processedImage->update();
//    
//    
//  }
}

void ImageHandler::processImage() {
  printf("processImage\n");
  
  const int screenW = ofGetWidth();
  const int screenH = ofGetHeight();
  
  int wid = originalImage->getWidth();
  int hig = originalImage->getHeight();
  
  int nWi = wid;
  int nHi = hig;
  int vbuffer = 0;
  int wbuffer = 0;
  
  if (screenH > screenW ) {
    cout << "Height is taller" << endl;
    nWi = hig * screenW/screenH;
    wbuffer = (wid - nWi) / 2.0;
  } else {
    cout << "Width is taller" << endl;
    nHi = wid * screenH/screenW;
    vbuffer = (hig - nHi) / 2.0;
  }
  
  printf("w:%i h:%i nWi:%i nHi:%i wbuffer:%i vbuffer:%i", wid, hig, nWi, nHi, wbuffer, vbuffer);
  
  processedImage->clone(*originalImage);
  
  fx.processImage(processedImage);
  
  processedImage->crop(wbuffer, vbuffer, nWi, nHi);
  processedImage->resize(screenW, screenH);
  processedImage->update();
  
//  fx.processImage(processedImage);  
  
}

void ImageHandler::draw() {
  if (active) {
    
    processedImage->draw(0.0, 0.0);
    
  }
}

ImageHandler::~ImageHandler() {};
