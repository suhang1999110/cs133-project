// TO-DO
// The ReLU activation function
// a child class of layer
#ifndef CS133_RELU_HPP
#define CS133_RELU_HPP

#include "../Layer.hpp"

// ReLU function:
// f(x) = max(x,0)
class Relu : public Layer {
public:
    Relu();
    ~Relu();
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name);
    void forward(std::vector<Eigen::MatrixXd> input);
};

#include "reLU.hpp"

#endif // CS133_RELU_HPP