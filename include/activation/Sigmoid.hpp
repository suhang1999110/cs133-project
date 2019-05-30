///@file ReLU.hpp
///@brief The Sigmoid activation function, a child class of layer
#ifndef CS133_SIGMOID_HPP
#define CS133_SIGMOID_HPP

#include "../Layer.hpp"

///@brief Class of Sigmoid activation function
///
/// Sigmoid: f(x) = 1/(1 + e^(-x));
class Sigmoid : public Layer {
public:
    Sigmoid();   ///< Constructor
    ~Sigmoid();  ///< Destructor
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              int node_num,
              int kernel_row,
              int kernel_col,
              int stride_row,
              int stride_col,
              std::string padding,
              std::string name);  ///<Initialize the Layer according to args
    void forward(std::vector<Eigen::MatrixXd> input);   ///< Spread forward to generate response
};

#include "sigmoid.hpp"

#endif // CS133_RELU_HPP