//
//  StateController.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/22/17.
//
//

#ifndef StateController_hpp
#define StateController_hpp

#include "ofMain.h"

namespace ct {
  
  class StateController {
    
  private:
    
    int state = 0;
    
  public:
    
    StateController();
    void nextState();
    void startOver();
    int getState();
    
    static const int RESTART = 0;
    static const int READY = 1;
    static const int INSTRUCTION_1 = 2;
    static const int TAKE_PHOTO = 3;
    static const int INSTRUCTION_2 = 4;
    static const int BRAIN_DATA = 5;
    static const int INSTRUCTION_3 = 6;
    static const int FINALIZE = 7;
    
  };
}

#endif /* StateController_hpp */
