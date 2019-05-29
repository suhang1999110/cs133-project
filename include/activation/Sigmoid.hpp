// TO-DO
// The Sigmoid activation function
// a child class of layer
#ifndef CS133_SIGMOID_HPP
#define CS133_SIGMOID_HPP

#include "../Layer.hpp"

class Sigmoid : public Layer {
public:
    Sigmoid();
    ~Sigmoid();
    void init();
    void forward(std::vector<Eigen::MatrixXd> input);
};

#include "sigmoid.hpp"

#endif // CS133_RELU_HPP