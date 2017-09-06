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
#include "GaussianBlur.hpp"

namespace ct {
  
  enum class EFFECTS { BLUR };
  
  class EffectHandler {
    
  private:
    
    GaussianBlur gBlur;
    
    std::map<EFFECTS, bool> activeEffects;
    
  public:
    
    void turnOnEffect(EFFECTS fx);
    void turnOffEffect(EFFECTS fx);
    ofImage processImage(ofImage &imageIn);
    
    void setup(int iWidth, int iHeight);
    void update();
    void draw();
    
    EffectHandler();
    ~EffectHandler();
    
  };
  
}

#endif /* EffectHandler_hpp */
