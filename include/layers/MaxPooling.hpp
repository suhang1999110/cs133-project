// TO-DO
// The max pooling layer
// a child class of layer
#ifndef CS133_LAYER_MAXPOOLING_HPP
#define CS133_LAYER_MAXPOOLING_HPP

#include "Layer.hpp"

class MaxPooling : public Layer {
public:
    MaxPooling();
    ~MaxPooling();
    void init(double pool_row,
              double pool_col,
              std::string padding,
              std::string name);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    int m_pool_row;
    int m_pool_col;
};

#include "maxPooling.hpp"

#endif