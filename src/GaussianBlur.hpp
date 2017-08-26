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

namespace ct {
  
class GaussianBlur {

  ofFbo passOne;
  ofFbo passTwo;
  
  ofShader blurX;
  ofShader blurY;
  
  ofVec2f resolution;
  shared_ptr<ofImage> blurred;
  
public:
  
  GaussianBlur(int iWidth, int iHeight);
  ~GaussianBlur();
  
  shared_ptr<ofImage> blurImage(ofVideoGrabber iOriginal, int iPasses);
  
};

}
#endif /* GaussianBlur_hpp */