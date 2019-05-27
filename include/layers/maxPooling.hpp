#ifndef CS133_LAYER_MAXPOOLING_IMPL_HPP
#define CS133_LAYER_MAXPOOLING_IMPL_HPP


// default constructor
MaxPooling::MaxPooling() {}

// default destructor
MaxPooling::~MaxPooling() {}

void
MaxPooling::init(double pool_row,
                 double pool_col,
                 std::string padding,
                 std::string name) {
    m_pool_row = pool_row;
    m_pool_col = pool_col;
    m_padding = padding;
    m_name = name;
    m_type = Pooling;
}

void
MaxPooling::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = input.size();
    m_input = input;
    m_row = m_input[0].rows();
    m_col = m_input[0].cols();

    for (int image = 0; image < m_in_size; ++image) {
        MatrixXd pool_result((m_row / m_pool_row), (m_col / m_pool_col));
        for (int row = 0; row < m_row; row += m_pool_row) {
            for (int col = 0; col < m_col; col += m_pool_col) {
                pool_result((row / m_pool_row), (col / m_pool_col)) = m_input[image].block<m_pool_row, m_pool_col>(row, col).maxCoeff();
            }
        }
        m_output.push_back(pool_result);
    }

    m_out_size = m_output.size();
}

#endif // CS133_LAYER_MAXPOOLING_IMPL_HPP