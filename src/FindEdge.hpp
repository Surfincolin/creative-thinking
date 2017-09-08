//
//  FindEdge.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/7/17.
//
//

#ifndef FindEdge_h
#define FindEdge_h

#include "Effect.hpp"

namespace ct {
  
  class FindEdge: public Effect {
    
  public:
    
    FindEdge() {
      
      addShader("shaders/findEdge.frag");
      
    }
    
    
    ~FindEdge() {
      
    }
  };
}

#endif /* FindEdge_h */
