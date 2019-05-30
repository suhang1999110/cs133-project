// Implementation of the
// Softmax activation function

Softmax::Softmax() {}

Softmax::~Softmax() {}

void
Softmax::init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              int node_num,
              int kernel_row,
              int kernel_col,
              int stride_row,
              int stride_col,
              std::string padding,
              std::string name) {
    m_type = Layer::Softmax;
    m_name = name;
}

void
Softmax::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = input.size();
    m_input = input;
    m_row = m_input[0].rows();
    m_col = m_input[0].cols();

    for (int i = 0; i < m_in_size; ++i) {
        Eigen::MatrixXd result(m_row, m_col);
        result.array() = (m_input[i].rowwise() - m_input[i].colwise().maxCoeff()).array().exp();
        Eigen::Array<double, 1, Eigen::Dynamic> colsums = result.colwise().sum();
        result.array().rowwise() /= colsums;
        m_output.push_back(result);
    }
    m_out_size = m_output.size();
}