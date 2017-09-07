 //
//  GaussianBlur.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 8/21/17.
//
//

#include "GaussianBlur.hpp"

using namespace ct;

GaussianBlur::GaussianBlur() {
  
  addShader("shaders/blurX.frag");
  addShader("shaders/blurY.frag");
  setPasses(6);
  
}

//void GaussianBlur::setAddtionalUniforms(ofShader &iShader) {
//  
//}

//void GaussianBlur::setup(int iWidth, int iHeight) {
//  
//  passOne.allocate(iWidth, iHeight, GL_RGBA, 0);
//  passTwo.allocate(iWidth, iHeight, GL_RGBA, 0);
//  
//  blurred = make_shared<ofImage>();
//  blurred->allocate(iWidth, iHeight, OF_IMAGE_COLOR);
//  
//  resolution = ofVec2f(iWidth, iHeight);
//  
//}

//shared_ptr<ofImage> GaussianBlur::blurImage(ofVideoGrabber iOriginal, int iPasses) {
//  
//  
//  passOne.begin();
//  blurX.begin();
//  iOriginal.draw(0,0);
//  blurX.end();
//  passOne.end();
//  
//  passTwo.begin();
//  blurY.begin();
//  passOne.draw(0,0);
//  blurY.end();
//  passTwo.end();
//  
//  
//  for (int i = 0; i < iPasses - 1; i++) {
//    
//    passOne.begin();
//    blurX.begin();
//    passTwo.draw(0,0);
//    blurX.end();
//    passOne.end();
//    
//    passTwo.begin();
//    blurY.begin();
//    passOne.draw(0,0);
//    blurY.end();
//    passTwo.end();
//    
//  }
//  
//  
//  passTwo.begin();
//  blurred->grabScreen(0, 0, passTwo.getWidth(), passTwo.getHeight());
//  passTwo.end();
//  
//  return blurred;
//  
//}

//void GaussianBlur::processEffect(ofImage &imageIn) {
//  
//  
//  passOne.begin();
//  ofClear(0, 0, 0);
//  blurX.begin();
//  imageIn.draw(0,0);
//  blurX.end();
//  passOne.end();
//  
//  passTwo.begin();
//  ofClear(0, 0, 0);
//  blurY.begin();
//  passOne.draw(0,0);
//  blurY.end();
//  passTwo.end();
//  
//  
//  for (int i = 0; i < 6 - 1; i++) {
//    
//    passOne.begin();
//    ofClear(0, 0, 0);
//    blurX.begin();
//    passTwo.draw(0,0);
//    blurX.end();
//    passOne.end();
//    
//    passTwo.begin();
//    ofClear(0, 0, 0);
//    blurY.begin();
//    passOne.draw(0,0);
//    blurY.end();
//    passTwo.end();
//    
//  }
//
//  passTwo.begin();
//  imageIn.grabScreen(0, 0, passTwo.getWidth(), passTwo.getHeight());
//  passTwo.end();
//
//  imageIn.mirror(true, false);
//  
//  return imageIn;
//  
//}

GaussianBlur::~GaussianBlur() {
  
  
}
