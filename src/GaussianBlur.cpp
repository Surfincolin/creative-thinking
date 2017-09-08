 //
//  GaussianBlur.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 8/21/17.
//
//

#include "GaussianBlur.hpp"

using namespace ct;

GaussianBlur::GaussianBlur() {
  
  addShader("shaders/blurX.frag");
  addShader("shaders/blurY.frag");
  setPasses(6);
  
}

GaussianBlur::~GaussianBlur() {
  
  
}
