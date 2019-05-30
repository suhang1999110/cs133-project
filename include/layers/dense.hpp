#ifndef CS133_LAYER_DENSE_IMPL_HPP
#define CS133_LAYER_DENSE_IMPL_HPP

// default constructor
Dense::Dense() {}

// default destructor
Dense::~Dense() {}

void
Dense::init(int cur_in_size,
            int cur_input_row,
            int cur_input_col,
            int node_num,
            int non_arg1,
            int non_arg2,
            int non_arg3,
            int non_arg4,
            std::string non_arg5,
            std::string name) {
    m_node_num = node_num;
    m_name = name;
    m_type = Layer::Dense;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = 1;
    m_output_row = m_node_num;
    m_output_col = 1;
}

void
Dense::init(Eigen::MatrixXd weight, Eigen::MatrixXd bias) {
    m_weight = weight;
    m_bias = bias;
}

void
Dense::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    m_output.push_back(m_weight * m_input[0] + m_bias);
}

#endif // CS133_LAYER_DENSE_HPP