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

void Effect::setup(ofVec2f iResolution, shared_ptr<ofFbo> iFbo) {
  resolution = iResolution;
  masterFbo = iFbo;
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
  
  for (auto i = 0; i < passes; i++) {
    for (auto shdr : effectShaders) {
      
      masterFbo->begin();
      shdr.begin();

      shdr.setUniform2f("resolution", resolution);
      setAddtionalUniforms(shdr);
      
      if (setOg) {
        ofClear(0, 0, 0);
        imageIn.draw(0, 0);
        setOg = false;
      } else {
        masterFbo->draw(0, 0);
      }

      shdr.end();
      masterFbo->end();
      
    }
  }
  
  masterFbo->begin();
  imageIn.grabScreen(0, 0, resolution.x, resolution.y);
  masterFbo->end();
  
}

Effect::~Effect() {};
