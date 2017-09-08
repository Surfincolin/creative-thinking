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
    
    ofVec2f resolution;
    int passes = 1;
    
  public:
    
    std::vector< shared_ptr<ofFbo> > fbos;
    std::vector< ofShader > effectShaders;
    
    Effect();
    ~Effect();
    
    void setup(ofVec2f iResolution, shared_ptr<ofFbo> iFbo, shared_ptr<ofFbo> jFbo);
    void addShader(string iFragFile);
    void setPasses(int iPasses) { passes = iPasses; };
    ofVec2f getResolution() { return resolution; };
    
    void processEffect(ofImage &imageIn);
    void setAddtionalUniforms(ofShader &iShader);
    
  };
  
}


#endif /* Effect_hpp */
