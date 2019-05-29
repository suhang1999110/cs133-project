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
  std::vector<std::string> input_path;
  input_path.push_back("test/test0.txt");
  input_path.push_back("test/test1.txt");
  input_path.push_back("test/test2.txt");
  input_path.push_back("test/test3.txt");
  input_path.push_back("test/test4.txt");
  input_path.push_back("test/test5.txt");
  input_path.push_back("test/test6.txt");
  input_path.push_back("test/test7.txt");
  input_path.push_back("test/test8.txt");
  input_path.push_back("test/test9.txt");

  // cv::Mat img = cv::imread(input_path);
  // Eigen::MatrixXd input(img.cols, img.rows);
  // cv2eigen(img, input);


  for (auto it = input_path.begin(); it != input_path.end(); ++it) {
    // LeNet-5
    Net net;
    net.init(model_path, weights_path);

    std::ifstream fin(*it);

    Eigen::MatrixXd input(28, 28);
    for(int i = 0; i < 28; ++i) {
      for(int j = 0; j < 28; ++j) {
        double buffer;
        fin>>buffer;
        input(i,j) = buffer / 256.0;
      }
    }

    Eigen::MatrixXd output = net.forward(input);

    int result = 0;
    int err = 10;
    for(int i = 0; i < 10; ++i) {
      if ( abs(output(i, 0) - 1) < err ) {
          err = abs(output(i, 0) - 1);
          result = i;
      }
    }
    std::cout << "The number in the picture is " << result << std::endl;
  }

  return 0;
}