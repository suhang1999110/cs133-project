// TO-DO
// The fully connected layer
// a child class of layer
#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include "Layer.hpp"

class Dense : public Layer {
public:
    Dense();
    ~Dense();
    void init(int node_num, std::string name);
    void init(Eigen::MatrixXd weights, Eigen::MatrixXd bias);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    int m_node_num;
    Eigen::MatrixXd m_weights;
    Eigen::MatrixXd m_bias;
};

#include "dense.hpp"

#endif