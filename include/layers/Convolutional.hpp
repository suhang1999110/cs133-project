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
    void init(double row,
              double col,
              double node_num,
              double kernal_row,
              double kernal_col,
              std::string name,
              std::string padding);
    void init(std::vector<std::vector<Eigen::MartixXd>> kernal);
    void forward(std::vector<Eigen::MatrixXd> input, std::vector<double> weight, MatrixXd bias);

protected:
    std::vector<std::vector<Eigen::MartixXd>> m_kernal;
    int m_kernal_row;
    int m_kernal_col;
    std::string m_padding;
};

#include "convolutional.hpp"

#endif