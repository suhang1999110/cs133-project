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
    void init(std::vector<std::vector<Eigen::MartixXd>> kernel,
              std::vector<double> weight,
              Eigen::MatrixXd bias);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    int m_node_num;
    // the row number of the input matrix
    int m_row;
    // the col number of the input matrix
    int m_col;
    std::vector<std::vector<Eigen::MartixXd>> m_kernel;
    int m_kernel_row;
    int m_kernel_col;
    int m_stride_row;
    int m_stride_col;
    std::vector<double> m_weight;
    Eigen::MartixXd m_bias;
    std::string m_padding;
};

#include "convolutional.hpp"

#endif