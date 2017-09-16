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
  
  activeEffects.insert(make_pair(EFFECTS::BLUR, false));
  activeEffects.insert( make_pair(EFFECTS::FINDEDGE, false));
  activeEffects.insert( make_pair(EFFECTS::BLENDER, false));
  
  firstFbo = make_shared<ofFbo>();
  secondFbo = make_shared<ofFbo>();
  
};

void EffectHandler::setup(int iWidth, int iHeight) {

  resolution.x = iWidth;
  resolution.y = iHeight;
  
  printf("Resolution %f, %f\n", resolution.x, resolution.y);
  
  firstFbo->allocate(resolution.x, resolution.y);
  secondFbo->allocate(resolution.x, resolution.y);
  
  auto findEdge = make_shared<FindEdge>();
  findEdge->setup(resolution, firstFbo, secondFbo);
  allEffects.insert( make_pair(EFFECTS::FINDEDGE, findEdge) );
  
  auto gBlur = make_shared<GaussianBlur>();
  gBlur->setup(resolution, firstFbo, secondFbo);
  allEffects.insert( make_pair(EFFECTS::BLUR, gBlur) );
  
  auto blender = make_shared<Blender>();
  blender->setup(resolution, firstFbo, secondFbo);
  allEffects.insert( make_pair(EFFECTS::BLENDER, blender) );
  
};

void EffectHandler::turnOnEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = true;
  
};

void EffectHandler::turnOffEffect(EFFECTS fx) {
  
  activeEffects.at(fx) = false;
  
};

void EffectHandler::processImage(shared_ptr<ofImage> imageIn) {
  
  // Original
  ofImage edges;
  ofImage gBlur;
  edges.clone(*imageIn);
  gBlur.clone(*imageIn);
  
  // findEdge
  if (activeEffects.at(EFFECTS::FINDEDGE)) {
    allEffects.at(EFFECTS::FINDEDGE)->processEffect(edges);
  }
  
  // Gaussian
  if (activeEffects.at(EFFECTS::BLUR)) {
    allEffects.at(EFFECTS::BLUR)->processEffect(gBlur);
  }
  
  if (activeEffects.at(EFFECTS::BLENDER)) {
    auto blender = static_pointer_cast<Blender>(allEffects.at(EFFECTS::BLENDER));
    blender->processEffect(imageIn, edges, gBlur);
  }
  
  
};


EffectHandler::~EffectHandler() {};
