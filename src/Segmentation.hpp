//
//  Segmentation.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/19/17.
//
//

#ifndef Segmentation_hpp
#define Segmentation_hpp

#include "ofMain.h"
#include "ofxOpenCv.h"

namespace ct {
  
  class Segmentation {
 
  public:
    
    Segmentation();
    std::vector<shared_ptr<ofImage>> getSegments(ofImage &input, int colorCount);
    
    
  private:
    
    ofImage input;
    //std::std::unique_ptr<ofImage> image;
    
  };
}

#endif /* Segmentation_hpp */
