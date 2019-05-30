///@file Layer.hpp
///@brief Interface of layer class
#ifndef CS133_LAYER_HPP
#define CS133_LAYER_HPP

#include <Eigen/Core>
#include <vector>
#include <cstddef>
#include <string>

/// @brief Layer base class
///
/// Will be inherited by many child class
class Layer {
public:
    ///@enum  The type of layers
    enum layerType {
      Conv,      ///< Convolutional layer
      Pooling,   ///< Pooling Layer
      Dense,     ///< Dence Layer
      Flatten,   ///< Flatten Layer
      Identity,  ///< Layer of Identity activavtion function
      ReLU,      ///< Layer of ReLU activavtion function
      Sigmoid,   ///< Layer of Sigmoid activavtion function
      Softmax    ///< Layer of Softmax activavtion function
    };

    /// default constructor
    Layer();

    /// virtual deconstructor
    virtual ~Layer();

    /// initialize the parameters (including input size, output size, number of nodes etc.)
    virtual void init(int cur_in_size,
                      int cur_input_row,
                      int cur_input_col,
                      int node_num,
                      int kernel_row,
                      int kernel_col,
                      int stride_row,
                      int stride_col,
                      std::string padding,
                      std::string name) = 0;
  
    /// compute the output of this layer
    virtual void forward(std::vector<Eigen::MatrixXd> input) = 0;
    
    // get number of neuron
    int node_num() const ;

    // get the row number of the input matrix
    int input_row() const;

    // get the col number of the input matrix
    int input_col() const;

    // get the row number of the output matrix
    int output_row() const;

    // get the col number of the output matrix
    int output_col() const;

    /// get input
    std::vector<Eigen::MatrixXd> input() const;

    /// get output
    std::vector<Eigen::MatrixXd> output() const;

    /// return the layer type
    layerType get_type() const;

    /// return the layer name
    std::string get_name() const;

    /// get the size of input
    int in_size() const;
  
    /// get the size of output
    int out_size() const;

protected:
    /// number of neurons
    int m_node_num;
    // the row number of the input matrix
    int m_row;
    // the col number of the input matrix
    int m_col;
    // the row number of the output matrix
    int m_output_row;
    // the col number of the output matrix
    int m_output_col;
    /// input
    std::vector<Eigen::MatrixXd> m_input;

    /// output
    std::vector<Eigen::MatrixXd> m_output;

    /// layer name
    std::string m_name;

    /// layer type (e.g. conv, pooling, dense)
    layerType m_type;

    /// number of input units of this hidden layers. Equal to the number of output units of the previous layer.
    int m_in_size;
    
    /// number of output units of this hidden layers. Equal to the number of input units of the next layer.
    int m_out_size;
};

#include "layer.hpp"

#endif