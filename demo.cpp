// demo will be presented on 31st May

#include "Net.hpp"
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>

int main(){
  // file path
  std::string model_path("test/");
  std::string weights_path("test/");
  std::string input_path("test/");
  // LeNet-5
  Net net;
  net.init(model_path, weights_path, "LeNet-5");
  // 
  cv::Mat img = cv::imread(input_path);
  Eigen::MatrixXd input(img.cols, img.rows);

  cv2eigen(img, input);

  net.set_input(input);
  net.forward();

  Eigen::MatrixXd output = net.output();

  std::cout<<"Output:\n"<<output;

  return 0;
}