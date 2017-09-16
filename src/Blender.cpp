//
//  Blender.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/8/17.
//
//

#include "Blender.hpp"

using namespace ct;

Blender::Blender() {
  
  addShader("shaders/colorDodge.frag");
  
}

void Blender::processEffect(shared_ptr<ofImage> imageIn, ofImage &iEdges, ofImage &iBlurred) {
  
  auto curFbo = fbos.at(0);
  auto &shdr = effectShaders.at(0);
  
  curFbo->begin();
  ofClear(0, 0, 0);
  shdr.begin();
  
  shdr.setUniform2f("resolution", getResolution() );
  shdr.setUniformTexture("image", *imageIn, 1);
  shdr.setUniformTexture("edges", iEdges, 2);
//  shdr.setUniform1f("opacity", 1.0);
//  shdr.setUniform1i("fN", 7);
//  shdr.setUniform1f("alpha", 0.732812524);
//  shdr.setUniform1f("beta", 0.228758186);
  
  iBlurred.draw(0,0);
  
  shdr.end();
  curFbo->end();
  
//  imageIn.draw(0,0);
//  iEdges.draw(0,0);
  
  
  ofPixels pix;
  curFbo->readToPixels(pix);
  imageIn->setFromPixels(pix);
  
}

Blender::~Blender() {
  
}
