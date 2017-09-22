//
//  PigmentLayer.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//

#include "PigmentLayer.hpp"

PigmentLayer::PigmentLayer() {
  ofDisableArbTex();
  fbo = make_shared<ofFbo>();
  fbo->allocate(1280, 720, GL_RGBA32F);
  fbo->begin();
  ofClear(0.f, 0.f, 0.f, 255.f);
  fbo->end();
}

PigmentLayer::~PigmentLayer() {
  
}


shared_ptr<ofFbo> PigmentLayer::update(shared_ptr<ofFbo> water, shared_ptr<ofFbo> noise, shared_ptr<ofFbo> temp, ofShader &shader) {
  temp->begin();
  ofClear(0.f, 0.f, 0.f, 0.f);
  shader.begin();
  shader.setUniformTexture("noise", noise->getTexture(), 1);
  shader.setUniformTexture("water", water->getTexture(), 2);
  fbo->draw(0, 0);
  shader.end();
  temp->end();
  
  shared_ptr<ofFbo> swap = fbo;
  fbo = temp;
  return swap;

}



