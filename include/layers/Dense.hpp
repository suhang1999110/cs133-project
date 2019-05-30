///@file Dense.hpp
///@brief Interface of dense layer
///
///A fully connected layer, just take the input, multiply
///it by weight and add bias to it and output the result.
#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include "../Layer.hpp"

///@brief Class of dense layer
///
///A fully connected layer, just take the input, multiply
///it by weight and add bias to it and output the result.
class Dense : public Layer {
public:
    Dense();   ///< Constructor
    ~Dense();  ///< Destructor
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              int node_num,
              int kernel_row,
              int kernel_col,
              int stride_row,
              int stride_col,
              std::string padding,
              std::string name);  ///< Initialize the layer with those arguments
    void init(Eigen::MatrixXd weight, Eigen::MatrixXd bias);   ///< Initialize the layer with given kernel and bias
    void forward(std::vector<Eigen::MatrixXd> input);   ///< Spread forward and get the response

private:
    Eigen::MatrixXd m_weight;   ///< Matrix to represent the weights
    Eigen::MatrixXd m_bias;     ///< Matrix to represent the bias
};

#include "dense.hpp"

#endif