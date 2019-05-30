// Implementation of the
// Softmax activation function
#ifndef CS133_SOFTMAX_IMPL_HPP
#define CS133_SOFTMAX_IMPL_HPP

Softmax::Softmax() {}

Softmax::~Softmax() {}

void
Softmax::init(int cur_in_size,
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
    m_type = Layer::Softmax;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = m_in_size;
    m_output_row = m_row;
    m_output_col = m_col;
}

void
Softmax::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    for (int i = 0; i < m_in_size; ++i) {
        Eigen::MatrixXd result(m_row, m_col);
        result.array() = (m_input[i].rowwise() - m_input[i].colwise().maxCoeff()).array().exp();
        Eigen::Array<double, 1, Eigen::Dynamic> colsums = result.colwise().sum();
        result.array().rowwise() /= colsums;
        m_output.push_back(result);
    }
}

#endif // CS133_SOFTMAX_IMPL_HPP