//
//  CameraHandler.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/5/17.
//
//

#ifndef CameraHandler_hpp
#define CameraHandler_hpp

#include "ofMain.h"

namespace ct {
 
  class CameraHandler {
    
  private:
    ofVideoGrabber cam;
    ofImage picSave;
    
    bool active = true;
    
    int camWidth;
    int camHeight;
    
  public:
    
    void standbyForPhoto();
    ofImage takePhoto();
    
    void update();
    void draw();
    
    CameraHandler();
    ~CameraHandler();
  
  };
  
  
}
#endif /* CameraHandler_hpp */
