// demo will be presented on 31st May

#include "include/Net.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <Eigen/Core>
// #include <opencv2/opencv.hpp>
// #include <opencv2/core/eigen.hpp>

int main(){
  // file path
  std::string model_path("resources/model.json");
  std::string weights_path("resources/weights.json");
  std::string input_path("test/test.txt");
  // LeNet-5
  Net net;
  net.init(model_path, weights_path);

  // cv::Mat img = cv::imread(input_path);
  // Eigen::MatrixXd input(img.cols, img.rows);

  // cv2eigen(img, input);

  std::ifstream fin(input_path);

  Eigen::MatrixXd input(28, 28);
  for(int i = 0;i < 28;++i){
    for(int j = 0;j < 28;++j){
      double buffer;
      fin>>buffer;
      input(i,j) = buffer / 256.0;
    }
  }

  

  Eigen::MatrixXd output = net.forward(input);

  std::cout<<"Output:\n"<<output;

  return 0;
}