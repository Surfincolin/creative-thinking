//
//  Blender.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/8/17.
//
//

#ifndef Blender_hpp
#define Blender_hpp

#include "ofMain.h"
#include "Effect.hpp"

namespace ct {
  
  class Blender: public Effect {
    
    
  public:
    
    void processEffect(shared_ptr<ofImage> imageIn, ofImage &iEdges, ofImage &iBlurred);
    
    Blender();
    ~Blender();
    
  };
  
}
#endif /* Blender_hpp */
