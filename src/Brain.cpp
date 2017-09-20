//
//  Brain.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/19/17.
//
//

#include "Brain.hpp"

using namespace ct;

Brain::Brain() {
  
  for (auto w : waves) {
    highs.insert(make_pair(w, 0));
    graphData.insert(make_pair(w, vector<float>() ));
  }
  
  for (int i = 0; i < segments; i++) {
    for (auto w : waves) {
      graphData.at(w).push_back(0.0);
    }
  }
  
  mindwave.setup();
  mindwave.start();
  
}

float Brain::getBrainWaveValue(std::string wave) {
  float val = 0.0;
  
  if (wave == "delta") val =	brainData.delta;
  if (wave == "theta") val =	brainData.theta;
  if (wave == "hAlpha") val =	brainData.highAlpha;
  if (wave == "lAlpha") val =	brainData.lowAlpha;
  if (wave == "hBeta") val =	brainData.highBeta;
  if (wave == "lBeta") val =	brainData.lowBeta;
  if (wave == "hGamma") val =	brainData.highGamma;
  if (wave == "lGamma") val =	brainData.lowGamma;
  if (wave == "attention") val =	brainData.attention;
  if (wave == "meditation") val =	brainData.meditation;
  
  return val;
}

ofColor Brain::getWaveColor(int n) {
  
  float phase = 0;
  float freq = PI*2/waves.size();
  int center = 128;
  int width = 127;
  
  int r = sin(freq * n + 2 + phase) * width + center;
  int g = sin(freq * n + 0 + phase) * width + center;
  int b = sin(freq * n + 4 + phase) * width + center;
  
  return ofColor(r, g, b);
}

// currently only returning theta
shared_ptr<vector<float>> Brain::analyze() {
  printf("Analyzing!");
  
  vector<float> &ref = graphData.at("theta");
  int crop = min((int)ref.size(), 10);
  
  auto tempData = make_shared<vector<float>>(ref.end() - crop, ref.end() );

  return tempData;
  
}

void Brain::update() {
  brainData = mindwave.getEegData();
  
  for (auto w : waves) {
    auto v = getBrainWaveValue(w);
    auto n = highs.at(w);
    highs.at(w) = (v > n) ? v : n;
  }
  
  int currentTime = ofGetFrameNum() / 60; //60fps
  if (currentTime > previousTime) {
    
    for (auto w : waves) {
      
      float rel = ofMap(getBrainWaveValue(w), 0.0, highs.at(w), 0.0, 1.0);
      
      graphData.at(w).erase(graphData.at(w).begin());
      graphData.at(w).push_back(rel);
    }
    
    previousTime = currentTime;

  }
  
}

void Brain::drawGraphOverlay() {
  
  ofSetLineWidth(5);
  
  const int width = ofGetWidth();
  const int height = ofGetHeight();
  
  float div = width/segments;
  float cN = 0;
  for (auto w : waves) {
    ofColor color = getWaveColor(cN);
    ofSetColor(color);
    
    ofVec2f prev(0.0,0.0);
    int i = 0;
    for (auto p : graphData.at(w)) {
      float x = div * (float)i;
      float y = p * height;
      if (i != 0) {
        ofDrawLine(prev.x, height-prev.y, x, height-y);
      }
      prev.x = x;
      prev.y = y;
      i++;
    }
    cN++;
  }
  
  ofSetHexColor(0xFFFFFF);
  
  ofDrawBitmapString(ofToString(ofGetFrameRate()) + " fps", 20, 20);
  ofDrawBitmapString("Press 'space' to take a photo", 20, 35);
  
  
  ofDrawBitmapString("BRAIN DATA", 20, 720-180);
  cN = 0;
  for (auto w : waves) {
    ofColor color = getWaveColor(cN);
    ofSetColor(color);
    ofDrawBitmapString(w + ": " + to_string((int)getBrainWaveValue(w)) + " ", 20, height - 165 + (15*cN));
    cN++;
  }

  
}
