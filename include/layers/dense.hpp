#ifndef CS133_LAYER_DENSE_IMPL_HPP
#define CS133_LAYER_DENSE_IMPL_HPP

// default constructor
Dense::Dense() {}

// default destructor
Dense::~Dense() {}

void
Dense::init(int node_num, std::string name) {
    m_node_num = node_num;
    m_name = name;
    m_type = Layer::Dense;
}

void
Dense::init(Eigen::MatrixXd weight, Eigen::MatrixXd bias) {
    m_weight = weight;
    m_bias = bias;
}

void
Dense::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = 1;
    m_input = input;

    m_output.push_back(m_weight * m_input[0] + m_bias);
    m_out_size = 1;
}

#endif // CS133_LAYER_DENSE_HPP