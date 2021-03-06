//
//  Segmentation.cpp
//  creativeThinking
//
//  Created by Colin Wageman on 9/19/17.
//
//

#include "Segmentation.hpp"

using namespace ct;

    
Segmentation::Segmentation() {
  
}

vector<shared_ptr<ofImage>> Segmentation::getSegments(ofImage &input, int colorCount) {
  
  ofImage temp;
  temp.clone(input);
  temp.resize(input.getWidth()/2, input.getHeight()/2);
  
  int rows = temp.getHeight();
  int cols = temp.getWidth();
  
  const int sampleCount = rows * cols;
  cv::Mat colorSamples(sampleCount, 1, CV_32FC3);
  
  // get pixels
  ofPixelsRef pixels = temp.getPixels();
  
  // matrix of samples
  cv::MatIterator_<cv::Vec3f> sampleIt = colorSamples.begin<cv::Vec3f>();
  for (int i = 0; i < sampleCount; i++) {
    int pos = i * 3;
    *sampleIt = cv::Vec3f(pixels[pos], pixels[pos+1], pixels[pos+2] );
    sampleIt++;
  }
  
  // call kmeans
  cv::Mat labels, clusters;
//  cv::kmeans(colorSamples, colorCount, labels, cv::TermCriteria(), 2, cv::KMEANS_RANDOM_CENTERS, clusters); //cv::TermCriteria::COUNT, 8, 0
  
  cv::kmeans(colorSamples, colorCount, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 3, cv::KMEANS_PP_CENTERS, clusters);
  
//  cv::kmeans(colorSamples, colorCount, labels, cv::TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), 2, cv::KMEANS_PP_CENTERS, clusters );
  
  vector<shared_ptr<ofImage>> layers;
  for (int i = 0; i < colorCount; ++i) {
    auto colorL = make_shared<ofImage>();
    colorL->allocate(cols, rows, OF_IMAGE_COLOR_ALPHA);
    layers.push_back(colorL);
    ofColor cColor = ofColor(clusters.at<cv::Vec3f>(i,0)[0], clusters.at<cv::Vec3f>(i,0)[1], clusters.at<cv::Vec3f>(i,0)[2]);
//    printf("color %i %i %i\n", cColor.r, cColor.g, cColor.b);
  }
  
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      int cluster_idx = labels.at<int>(x + y*cols,0);
      auto pointColor = ofColor(0,0,0,255);

      pointColor.r = clusters.at<cv::Vec3f>(cluster_idx, 0)[0];
      pointColor.g = clusters.at<cv::Vec3f>(cluster_idx, 0)[1];
      pointColor.b = clusters.at<cv::Vec3f>(cluster_idx, 0)[2];
      
      layers.at(cluster_idx)->setColor(x, y, pointColor);
      
    }
  }
  
  for (auto &img : layers) {
    img->resize(cols * 2, rows * 2);
//    img->update();
  }
  
  return layers;
  
  
}
    
