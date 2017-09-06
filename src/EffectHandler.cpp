//
//  EffectHandler.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#include "EffectHandler.hpp"

using namespace ct;

EffectHandler::EffectHandler() {
  
  activeEffects.insert( pair<EFFECTS, bool>(EFFECTS::BLUR, false));
  
};

void EffectHandler::setup(int iWidth, int iHeight) {

  gBlur.setup(iWidth, iHeight);
  
};

void EffectHandler::turnOnEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = true;
  
};

void EffectHandler::turnOffEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = false;
  
};

ofImage EffectHandler::processImage(ofImage &imageIn) {
  
  if ( activeEffects.at(EFFECTS::BLUR) ) {
    //Handle Blur
    gBlur.processEffect(imageIn);
  }
  
  return imageIn;
  
};

void EffectHandler::update() {

};

void EffectHandler::draw() {

};


EffectHandler::~EffectHandler() {};
