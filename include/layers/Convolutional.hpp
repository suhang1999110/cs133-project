// TO-DO
// The convolutional layer
// a child class of layer
#ifndef CS133_LAYER_CONVOLUTIONAL_HPP
#define CS133_LAYER_CONVOLUTIONAL_HPP

#include "Layer.hpp"

class Convolutional : public Layer {
public:
    Convolutional();
    ~Convolutional();
    void init(double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name);
    void init(std::vector<std::vector<Eigen::MartixXd>> kernel);
    void forward(std::vector<Eigen::MatrixXd> input, std::vector<double> weight, MatrixXd bias);

private:
    std::vector<std::vector<Eigen::MartixXd>> m_kernel;
    int m_kernel_row;
    int m_kernel_col;
    int m_stride_row;
    int m_stride_col;
    std::string m_padding;
};

#include "convolutional.hpp"

#endif