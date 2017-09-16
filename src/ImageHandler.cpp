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
  
  processedImage.allocate(1280, 720, OF_IMAGE_COLOR);
  
}

void ImageHandler::setOriginal(shared_ptr<ofImage> iPic) {
  printf("setOriginal");
//  originalImage->clear();
  originalImage = iPic;
  
  fx.setup(iPic->getWidth(), iPic->getHeight());
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
  if (active) {
    
    processedImage.update();
    
    
  }
}

void ImageHandler::processImage() {
  printf("processImage");
  
  auto wid = originalImage->getWidth();
  auto hig = originalImage->getHeight();
  
  int nHi = wid * 720.0/1280.0;
  int buffer = (hig - nHi) / 2.0;
  
  processedImage.clone(*originalImage);
  processedImage.crop(0, buffer, wid, nHi);
  processedImage.resize(1280, 720);
  
//  fx.processImage(originalImage);
  
}

void ImageHandler::draw() {
  if (active) {
    
    processedImage.draw(0.0, 0.0);
    
  }
}

ImageHandler::~ImageHandler() {};
