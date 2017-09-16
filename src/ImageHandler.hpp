//
//  ImageHandler.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#ifndef ImageHandler_hpp
#define ImageHandler_hpp

#include "ofMain.h"
#include "EffectHandler.hpp"

namespace ct {
  
  class ImageHandler {
    
  private:
    
    EffectHandler fx;
    shared_ptr<ofImage> originalImage;
    shared_ptr<ofImage> processedImage;
    
    bool active = true;
    
  public:
    
    void setOriginal(shared_ptr<ofImage> iPic);
    void resetOriginal();
    void processImage();
    
    void update();
    void draw();
    
    ImageHandler();
    ~ImageHandler();
    
  };
}


#endif /* ImageHandler_hpp */
