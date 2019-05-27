#ifndef CS133_LAYER_HPP
#define CS133_LAYER_HPP

#include <Eigen/Core>
#include <vector>
#include <cstddef>
#include <string>

// layer base class
class Layer {
public:
    enum layerType {
      Conv, Pooling, Dense, Flatten
    };
    // default constructor
    Layer();

    // virtual deconstructor
    virtual ~Layer();

    // initialize the parameters (including input size, output size, number of nodes etc.)
    virtual void init() = 0;
  
    // compute the output of this layer
    virtual void forward() = 0;
  
    // return the layer type
    layerType get_type() const;

    // return the layer name
    std::string get_name() const;

    // return the m_padding
    std::string get_padding() const;

    // return output
    Eigen::MatrixXd output() const;

    // get number of neuron(node)
    size_t num_node() const;

    // get the row number of the input matrix
    int row() const;

    // get the row number of the input matrix
    int col() const;

    // get the size of input
    int in_size() const;
  
    // get the size of output
    int out_size() const;

protected:
    size_t m_node_num;
    // input
    std::vector<Eigen::MatrixXd> m_input;
    // output
    std::vector<Eigen::MatrixXd> m_output;
    // layer name
    std::string m_name;
    // layer type (e.g. conv, pooling, dense)
    layerType m_type;
    // variable indicates whether the input matrix need padding
    std::string m_padding;
    // the row number of the input matrix
    const int m_row;
    // the col number of the input matrix
    const int m_col;
    // number of input units of this hidden layers. Equal to the number of output units of the previous layer.
    const int m_in_size;
    // number of output units of this hidden layers. Equal to the number of input units of the next layer.
    const int m_out_size;
};

#include "layer.hpp"

#endif