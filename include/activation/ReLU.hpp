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
    void init();
    void forward(std::vector<Eigen::MatrixXd> input);
};

#include "reLU.hpp"

#endif // CS133_RELU_HPP