//
//  WaterColorCanvas.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//
#include "WaterColorCanvas.hpp"

WaterColorCanvas::WaterColorCanvas() {
  ofDisableArbTex();
  noiseShader.load("shaders/passthrough.vert", "shaders/simplexNoise.frag");
  waterBleedingShader.load("shaders/passthrough.vert", "shaders/waterBleeding.frag");
  waterRenderShader.load("shaders/passthrough.vert", "shaders/waterRender.frag");
  pigmentFixShader.load("shaders/passthrough.vert", "shaders/pigmentFix.frag");
  pigmentRenderShader.load("shaders/passthrough.vert", "shaders/pigmentRender.frag");
  blurShader.load("shaders/passthrough.vert", "shaders/blur.frag");
  pigmentShader.load("shaders/passthrough.vert", "shaders/pigmentBleeding.frag");
  
  const int width = ofGetWidth();
  const int height = ofGetHeight();
  
  tempFbo = make_shared<ofFbo>();
  tempFbo->allocate(width, height, GL_RGBA32F); //temporary buffer
  noiseFbo = make_shared<ofFbo>();
  noiseFbo->allocate(width, height, GL_RGBA32F); //noise
  waterFbo = make_shared<ofFbo>();
  waterFbo->allocate(width, height, GL_RGBA32F); //water
  paperFbo = make_shared<ofFbo>();
  paperFbo->allocate(width, height, GL_RGBA32F); //fixed color
  paperFboTwo = make_shared<ofFbo>();
  paperFboTwo->allocate(width, height, GL_RGBA32F);
  

  master = make_shared<ofFbo>();
  master->allocate(width, height, GL_RGBA32F);
  clearLayers();
}

//--------------------------------------------------------------
void WaterColorCanvas::update() {
  noiseFbo = applyShader(noiseShader, noiseFbo, SHADING_TYPE_NOISE);
  
  for (int i = 0; i < pigments.size(); i ++) {
    tempFbo = pigments[i].update(waterFbo, noiseFbo, tempFbo, pigmentShader);
  }

  waterFbo = applyShader(waterBleedingShader, waterFbo, SHADING_TYPE_WATER_BLEEDING);
  
  for (int i = 0; i < pigments.size(); i ++)  {
    paperFbo = applyShader(pigmentFixShader, paperFbo, SHADING_TYPE_PIGMENT_FIX, i);
  }

  paperFbo = applyShader(blurShader, paperFbo, SHADING_TYPE_BLUR);
}

//--------------------------------------------------------------
shared_ptr<ofFbo> WaterColorCanvas::draw() {

  master->begin();
  
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  waterRenderShader.begin();
  waterRenderShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  waterFbo->draw(0, 0);
  waterRenderShader.end();

  glBlendFunc(GL_ZERO, GL_SRC_COLOR);
  paperFbo->draw(0, 0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  master->end();
  
  for (int i = 0; i < pigments.size(); i ++)  {
    tempFbo = applyShader(pigmentRenderShader, pigments[i].fbo, SHADING_TYPE_PIGMENT_RENDER, i);
  
    master->begin();
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    tempFbo->draw(0,0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    master->end();
    
  }
  
//  glDisable(GL_BLEND);
//  ofEnableAlphaBlending();
//  ofBlendMode(OF_BLENDMODE_SCREEN);
//  master->draw(0, 0);
  return master;
//  ofBlendMode(OF_BLENDMODE_ALPHA);
}

//--------------------------------------------------------------
shared_ptr<ofFbo> WaterColorCanvas::applyShader(ofShader& shader, shared_ptr<ofFbo> fbo, int type, int pigmentNum) {
  tempFbo->begin();
  ofClear(0.f, 0.f, 0.f, 0.f);
  shader.begin();
  shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  switch (type) {
    case SHADING_TYPE_NOISE:
    shader.setUniform1f("time", (float) ofGetFrameNum());
    break;
    case SHADING_TYPE_WATER_BLEEDING:
    shader.setUniformTexture("noise", noiseFbo->getTexture(), 1);
    shader.setUniformTexture("water", waterFbo->getTexture(), 2);
    break;
    case SHADING_TYPE_WATER_RENDER:
    break;
    case SHADING_TYPE_PIGMENT_FIX:
    shader.setUniformTexture("pigment", pigments[pigmentNum].fbo->getTexture(), 1);
    shader.setUniform1f("r", pigments[pigmentNum].color.r);
    shader.setUniform1f("g", pigments[pigmentNum].color.g);
    shader.setUniform1f("b", pigments[pigmentNum].color.b);
    break;
    case SHADING_TYPE_PIGMENT_RENDER:
    shader.setUniform1f("r", pigments[pigmentNum].color.r);
    shader.setUniform1f("g", pigments[pigmentNum].color.g);
    shader.setUniform1f("b", pigments[pigmentNum].color.b);
    break;
    case SHADING_TYPE_BLUR:
    shader.setUniformTexture("noise", noiseFbo->getTexture(), 1);
    shader.setUniformTexture("water", waterFbo->getTexture(), 2);
    break;
  }
  
  fbo->draw(0, 0);
  shader.end();
  tempFbo->end();
  
  std::swap(tempFbo, fbo);
  return fbo;
}

//--------------------------------------------------------------
void WaterColorCanvas::beginPigmentDraw(int i) {
  if (i < pigments.size()) {
    currentPigment = i;
    pigments[i].fbo->begin();
  }
}

//--------------------------------------------------------------
void WaterColorCanvas::endPigmentDraw() {
  pigments[currentPigment].fbo->end();
}

//--------------------------------------------------------------
void WaterColorCanvas::beginWaterDraw() {
  waterFbo->begin();
}

//--------------------------------------------------------------
void WaterColorCanvas::endWaterDraw() {
  waterFbo->end();
}


//--------------------------------------------------------------
void WaterColorCanvas::clearLayers() {
  clearFbo(waterFbo, 0, 0, 0, 255);
  clearFbo(paperFbo, 255, 255, 255, 255);
  clearFbo(paperFboTwo, 255, 255, 255, 255);
  clearFbo(master, 255, 255, 255, 0);
  
  for (int i = 0; i < pigments.size(); i ++) {
    clearFbo(pigments[i].fbo, 0, 0, 0, 255);
  }
}

//--------------------------------------------------------------
void WaterColorCanvas::clearFbo(shared_ptr<ofFbo> fbo, int r, int g, int b, int a) {
  fbo->begin();
  ofClear(r, g, b, a);
  fbo->end();
}

//--------------------------------------------------------------
void WaterColorCanvas::addPigment(ofColor color) {
  PigmentLayer p;
  p.color = color;
  pigments.push_back(p);
}
