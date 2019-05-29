// TO-DO
// The fully connected layer
// a child class of layer
#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include "../Layer.hpp"

class Dense : public Layer {
public:
    Dense();
    ~Dense();
    void init(int cut_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              std::string name);
    void init(Eigen::MatrixXd weight, Eigen::MatrixXd bias);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    Eigen::MatrixXd m_weight;
    Eigen::MatrixXd m_bias;
};

#include "dense.hpp"

#endif