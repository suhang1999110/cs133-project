// demo will be presented on 31st May

#include "include/Net.hpp"
#include <iostream>
#include <string>
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

  

  Eigen::MatrixXd output = net.forward(input);

  std::cout<<"Output:\n"<<output;

  return 0;
}