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
#include "ofxPhoto.h"

namespace ct {
 
  class CameraHandler {
    
  private:
    
    bool busy = false;
    bool newImage = false;
    
    int camWidth;
    int camHeight;
    
    ofxPhoto photo;
    bool bCamIsBusy;
    shared_ptr<ofImage> original;
    unsigned char *pic;
    
  public:
    
    const bool newPhoto() { return newImage; };
    void takePhoto();
    shared_ptr<ofImage> getPhoto();
    
    void update();
    void draw();
    
    void keyPressed  (ofKeyEventArgs& eventArgs);
    
    CameraHandler();
    ~CameraHandler();
  
  };
  
  
}
#endif /* CameraHandler_hpp */
