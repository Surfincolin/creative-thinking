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
  
}

void ImageHandler::setOriginal(ofImage iPic) {
  originalImage.clear();
  
  fx.setup(iPic.getWidth(), iPic.getHeight());
  fx.turnOnEffect(EFFECTS::BLUR);
  fx.turnOnEffect(EFFECTS::FINDEDGE);
  fx.turnOnEffect(EFFECTS::BLENDER);

  originalImage.clone(iPic);
  processImage();
  active = true;
}

void ImageHandler::resetOriginal() {
  active = false;
  originalImage.clear();
}

void ImageHandler::update() {
  if (active) {
    
    originalImage.update();
    
    
  }
}

void ImageHandler::processImage() {
  
  fx.processImage(originalImage);
  
}

void ImageHandler::draw() {
  if (active) {
    
    originalImage.draw(0.0, 0.0);
    
  }
}

ImageHandler::~ImageHandler() {};
