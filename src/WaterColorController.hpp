//
//  WaterColorController.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/21/17.
//
//

#ifndef WaterColorController_hpp
#define WaterColorController_hpp

#include "ofMain.h"
#include "WaterColorCanvas.hpp"

namespace ct {
  
  class WaterColorController {
    
  private:
    
  public:
    
    WaterColorController();
    
    void setup();
    void update();
    std::shared_ptr<ofFbo> draw();
    
    void strokeDraw();
    void imageLayerDraw();
    void clearLayers();
    
    void addColor(ofColor iColor);
    void resetColors();
    
    void addColorLayer(shared_ptr<ofImage> iImage, ofColor iColor);
    
    
    ofImage bg;
    ofImage brush;
    
    WaterColorCanvas canvas;
    
    void mPressed ();
    void mReleased ();
    
    ofPoint pos, prev, vec;
    float width, currentWidth;
    int currentPigment;
    int colorCount = 0;
    bool pressed = false;
    
    int state;
    static const int STATE_WATER = 0;
    static const int STATE_PIGMENT = 1;
    static const int STATE_MIX = 2;
    
    std::vector<std::shared_ptr<ofImage>> imageLayers;
    int waterbrush = 0;
  };
  
}

#endif /* WaterColorController_hpp */
