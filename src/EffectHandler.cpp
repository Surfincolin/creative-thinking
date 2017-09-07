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
  
  masterFbo = make_shared<ofFbo>();
  
};

void EffectHandler::setup(int iWidth, int iHeight) {

  resolution.x = iWidth;
  resolution.y = iHeight;
  
  masterFbo->allocate(resolution.x, resolution.y);
  
  auto gBlur = make_shared<GaussianBlur>();
  gBlur->setup(resolution, masterFbo);
  allEffects.insert( make_pair(EFFECTS::BLUR, gBlur) );
  
};

void EffectHandler::turnOnEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = true;
  
};

void EffectHandler::turnOffEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = false;
  
};

void EffectHandler::processImage(ofImage &imageIn) {
  
  for (auto fx : allEffects) {
    
    if (activeEffects.at(fx.first)) {
      
      fx.second->processEffect(imageIn);
      
    }
    
    
  }
  
  
//  if ( activeEffects.at(EFFECTS::BLUR) ) {
//    //Handle Blur
//    gBlur.processEffect(imageIn);
//  }
//  
//  return imageIn;
  
};


EffectHandler::~EffectHandler() {};
