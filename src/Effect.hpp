//
//  Effect.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/7/17.
//
//

#ifndef Effect_hpp
#define Effect_hpp

#include <stdio.h>
#include <vector>
#include "ofMain.h"

namespace ct {
  
  class Effect {
    
  private:
    
    shared_ptr<ofFbo> masterFbo;
    std::vector< ofShader > effectShaders;
    
    ofVec2f resolution;
    int passes = 1;
    
  public:
    
    Effect();
    ~Effect();
    
    void setup(ofVec2f iResolution, shared_ptr<ofFbo> iFbo);
    void addShader(string iFragFile);
    void setPasses(int iPasses) { passes = iPasses; };
    
    void processEffect(ofImage &imageIn);
    void setAddtionalUniforms(ofShader &iShader);
    
  };
  
}


#endif /* Effect_hpp */
