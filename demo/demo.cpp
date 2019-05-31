#include "../include/Net.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <Eigen/Core>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;
using namespace py::literals;

Eigen::MatrixXd convert(string);

int main(){
  py::scoped_interpreter guard{};
  // file path
  string model_path("model.json");
  string weights_path("weights.json");

  vector<string> input_path;
  
  input_path.push_back("0.png");
  input_path.push_back("1.png");
  input_path.push_back("2.png");
  input_path.push_back("3.png");
  input_path.push_back("4.png");
  input_path.push_back("5.png");
  input_path.push_back("6.png");
  input_path.push_back("7.png");
  input_path.push_back("8.png");
  input_path.push_back("9.png");

  for (auto it = input_path.begin(); it != input_path.end(); ++it) {
    // LeNet-5
    Net net;
    net.init(model_path, weights_path);

    Eigen::MatrixXd input = convert(*it);

    Eigen::MatrixXd output = net.forward(input);
    int result;
    double err = 10;
    for (int i = 0; i < 10; ++i) {
      if ( abs(output(i, 0) - 1) < err ) {
          err = abs(output(i, 0) - 1);
          result = i;
      }
    }
    cout << "The number in the picture is " << result << endl;
  }

  return 0;
}

Eigen::MatrixXd
convert(string filename){
  auto locals = py::dict("filename"_a = filename);
  py::exec(R"(
    from PIL import Image
    import numpy as np
    im = Image.open(filename)
    im = im.convert('L')
    width,height = im.size
    data = list(im.getdata())

    file = open(filename.split('.')[0] + '.txt','w')
    for i in range(height):
      for j in range(width):
        file.write(str(data[i*width + j]))
        file.write(' ')
      file.write('\n')
    file.close()
    name = filename.split('.')[0] + '.txt'
  )", py::globals(), locals);
  
  std::string name = locals["name"].cast<std::string>();
  int height = locals["height"].cast<int>();
  int width = locals["width"].cast<int>();

  Eigen::MatrixXd mat(height, width);

  ifstream fin(name);
  for(int i = 0;i < height;++i){
    for(int j = 0;j < width;++j){
      double buffer;
      fin>>buffer;
      mat(i,j) = buffer / 255.0;
    }
  }
  return mat;
}
