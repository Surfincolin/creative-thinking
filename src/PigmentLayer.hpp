//
//  PigmentLayer.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//

#ifndef PigmentLayer_hpp
#define PigmentLayer_hpp

//#pragma once

#include "ofMain.h"

class PigmentLayer {
public:
  PigmentLayer();
  ~PigmentLayer();
  std::shared_ptr<ofFbo> update(std::shared_ptr<ofFbo> water, std::shared_ptr<ofFbo> noise, std::shared_ptr<ofFbo> temp, ofShader &shader);
  ofColor color;
  std::shared_ptr<ofFbo> fbo;
};


#endif /* PigmentLayer_hpp */
