///@file ReLU.hpp
///@brief The ReLU activation function, a child class of layer
#ifndef CS133_RELU_HPP
#define CS133_RELU_HPP

#include "../Layer.hpp"


///@brief Activation function of ReLU
///
/// ReLU function: f(x) = max(x,0)
class ReLU : public Layer {
public:
    ReLU();   ///<Constructor
    ~ReLU();  ///<Destructor
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
    void forward(std::vector<Eigen::MatrixXd> input);  ///< Spread forward to generate response
};

#include "reLU.hpp"

#endif // CS133_RELU_HPP