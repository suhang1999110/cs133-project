// TO-DO
// The max pooling layer
// a child class of layer
#ifndef CS133_LAYER_MAXPOOLING_HPP
#define CS133_LAYER_MAXPOOLING_HPP

#include "Layer.hpp"

class MaxPooling : public Layer {
public:
    Pooling();
    ~Pooling();
    void init(Eigen::Matrix input_matrix);
    void forward();
};

#include "maxPooling.hpp"

#endif