// Implementation of the
// Sigmoid activation function
#ifndef CS133_SIGMOID_IMPL_HPP
#define CS133_SIGMOID_IMPL_HPP

Sigmoid::Sigmoid() {}

Sigmoid::~Sigmoid() {}

void
Sigmoid::init(int cur_in_size,
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
    m_type = Layer::Sigmoid;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = m_in_size;
    m_output_row = m_row;
    m_output_col = m_col;
}

void
Sigmoid::forward(std::vector<Eigen::MatrixXd> input){
    m_input = input;

    for (int i = 0; i < m_in_size; ++i) {
        m_output.push_back(1 / (1 + (-input[i].array()).exp()));
    }
}

#endif //CS133_SIGMOID_IMPL_HPP