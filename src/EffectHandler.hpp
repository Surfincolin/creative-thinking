//
//  EffectHandler.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#ifndef EffectHandler_hpp
#define EffectHandler_hpp

#include "ofMain.h"
#include "Effect.hpp"
#include "GaussianBlur.hpp"
#include "FindEdge.hpp"
#include "Blender.hpp"

namespace ct {
  
  enum class EFFECTS { BLUR, FINDEDGE, BLENDER };
  
  class EffectHandler {
    
  private:
    
    ofVec2f resolution;
    std::shared_ptr<ofFbo> firstFbo;
    std::shared_ptr<ofFbo> secondFbo;
    
    std::map<EFFECTS, bool> activeEffects;
    std::map<EFFECTS, shared_ptr<Effect> > allEffects;
    
  public:
    
    void turnOnEffect(EFFECTS fx);
    void turnOffEffect(EFFECTS fx);
    void processImage(shared_ptr<ofImage> imageIn);
    
    void setup(int iWidth, int iHeight);
    void update();
    void draw();
    
    EffectHandler();
    ~EffectHandler();
    
  };
  
}

#endif /* EffectHandler_hpp */
