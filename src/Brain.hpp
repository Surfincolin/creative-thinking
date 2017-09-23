//
//  Brain.hpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/19/17.
//
//

#ifndef Brain_hpp
#define Brain_hpp

#include "ofMain.h"
#include "ofxBrainWave.h"

namespace ct {
  
  class Brain {
    
  public:
    
    Brain();
    void update();
    void drawGraphOverlay();
    float getBrainWaveValue(std::string wave);
    ofColor getWaveColor(int n);
    std::shared_ptr<std::vector<float>> analyze();
    void startRecording();
    void stopRecording();
    void resetHighs();
    
    std::shared_ptr<std::map<std::string, float>> latestData;
//    std::vector<std::string> waves = { "delta", "theta", "hAlpha", "lAlpha", "hBeta", "lBeta", "hGamma", "lGamma", "attention", "meditation" };
    std::vector<std::string> waves = { "delta", "theta", "hAlpha", "lAlpha", "hBeta", "lBeta", "hGamma", "lGamma" };
    
  private:
    
    int segments = 50;
    ofxBrainWave mindwave;
    EegData brainData;
    
    
    std::map<std::string, float> highs;
    std::map<std::string, std::vector<float> > graphData;
    int previousTime = 0;
    
  };
  
}

#endif /* Brain_hpp */
