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

namespace ct {
  
  enum class EFFECTS { BLUR };
  
  class EffectHandler {
    
  private:
    
    ofVec2f resolution;
    std::shared_ptr<ofFbo> masterFbo;
    
    std::map<EFFECTS, bool> activeEffects;
    std::map<EFFECTS, shared_ptr<Effect> > allEffects;
    
  public:
    
    void turnOnEffect(EFFECTS fx);
    void turnOffEffect(EFFECTS fx);
    void processImage(ofImage &imageIn);
    
    void setup(int iWidth, int iHeight);
    void update();
    void draw();
    
    EffectHandler();
    ~EffectHandler();
    
  };
  
}

#endif /* EffectHandler_hpp */
