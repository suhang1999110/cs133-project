#ifndef CS133_LAYER_FLATTEN_HPP
#define CS133_LAYER_FLATTEN_HPP

#include "../Layer.hpp"

class Flatten : public Layer {
public:
    Flatten();
    ~Flatten();
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
};

#include "flatten.hpp"

#endif