//
//  Effect.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/7/17.
//
//

#include "Effect.hpp"

using namespace ct;

Effect::Effect() {
  ofDisableArbTex();
  
}

void Effect::setup(ofVec2f iResolution, shared_ptr<ofFbo> iFbo, shared_ptr<ofFbo> jFbo) {
  resolution = iResolution;
  fbos.push_back(iFbo);
  fbos.push_back(jFbo);
}

void Effect::addShader(string iFragFile) {
  
  auto shdr = ofShader();
  shdr.load("shaders/passthrough.vert", iFragFile);
  effectShaders.push_back( shdr );
  
}

void Effect::setAddtionalUniforms(ofShader &iShader) {
  
}

void Effect::processEffect(ofImage &imageIn) {
  bool setOg = true;
  auto lastFbo = 1;
  
  for (auto i = 0; i < passes; i++) {
    for (auto &shdr : effectShaders) {
      
      auto curFbo = fbos.at(lastFbo % 2);
      auto prevFbo = fbos.at( (lastFbo-1) % 2);
      
      curFbo->begin();
      ofClear(0, 0, 0);
      
      shdr.begin();
      
      shdr.setUniform2f("resolution", resolution);
      setAddtionalUniforms(shdr);
      
      if (setOg) {
        imageIn.draw(0, 0);
        setOg = false;
      } else {
        prevFbo->draw(0,0);
      }

      shdr.end();
      curFbo->end();
      
      lastFbo++;
    
    }
  }
  
  ofPixels pix;
  fbos.at( (lastFbo-1) % 2)->readToPixels(pix);
  
  imageIn.setFromPixels(pix);
  
}

Effect::~Effect() {};
