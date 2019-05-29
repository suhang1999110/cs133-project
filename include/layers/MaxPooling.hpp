// TO-DO
// The max pooling layer
// a child class of layer
#ifndef CS133_LAYER_MAXPOOLING_HPP
#define CS133_LAYER_MAXPOOLING_HPP

#include "../Layer.hpp"

class MaxPooling : public Layer {
public:
    MaxPooling();
    ~MaxPooling();
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    int m_pool_row;
    int m_pool_col;
    std::string m_padding;
};

#include "maxPooling.hpp"

#endif