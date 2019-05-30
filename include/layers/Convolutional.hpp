///@file Convolutional.hpp
///@brief A layer class doing convolution
#ifndef CS133_LAYER_CONVOLUTIONAL_HPP
#define CS133_LAYER_CONVOLUTIONAL_HPP

#include "../Layer.hpp"

///@brief Class of convolutional layer
///
/// Doing convolution for the input data
class Convolutional : public Layer {
public:
    Convolutional();   ///<Constructor
    ~Convolutional();  ///<Destructor
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              int node_num,
              int kernel_row,
              int kernel_col,
              int stride_row,
              int stride_col,
              std::string padding,
              std::string name);  ///<Initialize the layer with args
    void init(std::vector<std::vector<Eigen::MatrixXd>> kernel,
              std::vector<double> bias);   ///< Initialize the layer with given kernel and bias
    void forward(std::vector<Eigen::MatrixXd> input);   ///< Spread forward to get the linux
    int kernel_row() const;   ///< Get the number of rows
    int kernel_col() const;   ///< Get the number of columns

private:
    std::vector<std::vector<Eigen::MatrixXd>> m_kernel;  ///< A matrix of matrix
    int m_kernel_row;   ///< Number of rows in kernel
    int m_kernel_col;   ///< Number of columns in kernel
    int m_stride_row;   ///< Number of rows in stride
    int m_stride_col;   ///< Number of columns in stride
    std::vector<double> m_bias;   ///< Vector of number to represent the bias
    std::string m_padding;   ///< Indicate whether it is needed to fill the data to certain size
};

#include "convolutional.hpp"

#endif