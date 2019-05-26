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
    void init(double input_row,
              double input_col,
              double input_size,
              );
    void forward();

protected:
    std::vector<Eigen::MartixXd> kernal;
};

#include "convolutional.hpp"

#endif