//
//  GaussianBlur.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 8/21/17.
//
//

#ifndef GaussianBlur_hpp
#define GaussianBlur_hpp

#include "ofMain.h"
#include "Effect.hpp"

namespace ct {
  
  class GaussianBlur: public Effect {

  //  ofFbo passOne;
  //  ofFbo passTwo;
  //  
  //  ofShader blurX;
  //  ofShader blurY;
  //  
  //  ofVec2f resolution;
  //  shared_ptr<ofImage> blurred;
    
  public:
    
  //  void setup(int iWidth, int iHeight);
  //
    GaussianBlur();
    ~GaussianBlur();
    
//    void setAddtionalUniforms(ofShader &iShader);
  //
  //  shared_ptr<ofImage> blurImage(ofVideoGrabber iOriginal, int iPasses);
  //  void processEffect(ofImage &imageIn);
    
  };

}
#endif /* GaussianBlur_hpp */
