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
            double node_num,
            double kernel_row,
            double kernel_col,
            double stride_row,
            double stride_col,
            std::string padding,
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