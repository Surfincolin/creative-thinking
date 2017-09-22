//
//  WaterColorCanvas.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//

#ifndef WaterColorCanvas_hpp
#define WaterColorCanvas_hpp

#pragma once

#include "ofMain.h"
#include "PigmentLayer.hpp"

class WaterColorCanvas {
  
public:
  WaterColorCanvas();
  void update();
  void draw();
  void addPigment(ofColor color);
  void beginPigmentDraw(int i);
  void endPigmentDraw();
  void beginWaterDraw();
  void endWaterDraw();
  void clearLayers();
  void clearPigments();
  bool pressed;
  
private:
  
  std::shared_ptr<ofFbo> applyShader(ofShader& shader, std::shared_ptr<ofFbo> fbo, int type, int pigmentNum = 0);
  void clearFbo(std::shared_ptr<ofFbo> fbo, int r, int g, int b);
  
  ofColor color;
  ofShader noiseShader, waterBleedingShader, waterRenderShader, pigmentFixShader, pigmentRenderShader, blurShader, pigmentShader;;
  std::shared_ptr<ofFbo> tempFbo, noiseFbo, waterFbo, paperFbo, paperFboTwo;
  vector<PigmentLayer> pigments;
  int currentPigment;
  
  ofPoint pos, prev, vec, adj;
  float width, cwidth;
  
  int state;
  
  static const int SHADING_TYPE_NOISE = 0;
  static const int SHADING_TYPE_WATER_BLEEDING = 1;
  static const int SHADING_TYPE_WATER_RENDER = 2;
  static const int SHADING_TYPE_PIGMENT_FIX = 3;
  static const int SHADING_TYPE_PIGMENT_RENDER = 4;
  static const int SHADING_TYPE_BLUR = 5;
};

#endif /* WaterColorCanvas_hpp */
