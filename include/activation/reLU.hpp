// Implementation of the
// ReLU activation function
#ifndef CS133_RELU_IMPL_HPP
#define CS133_RELU_IMPL_HPP

ReLU::ReLU() {}

ReLU::~ReLU() {}

void
ReLU::init(int cur_in_size,
           int cur_input_row,
           int cur_input_col,
           int non_arg1,
           int non_arg2,
           int non_arg3,
           int non_arg4,
           int non_arg5,
           std::string non_arg6,
           std::string name) {
    m_name = name;
    m_type = Layer::ReLU;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = m_in_size;
    m_output_row = m_row;
    m_output_col = m_col;
}

void
ReLU::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    for(int i = 0; i < m_in_size; ++i) {
        m_output.push_back(input[i].cwiseMax(0));
    }
}

#endif // CS133_RELU_IMPL_HPP