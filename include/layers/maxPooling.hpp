#ifndef CS133_LAYER_MAXPOOLING_IMPL_HPP
#define CS133_LAYER_MAXPOOLING_IMPL_HPP


// default constructor
MaxPooling::MaxPooling() {}

// default destructor
MaxPooling::~MaxPooling() {}

void
MaxPooling::init(int cur_in_size,
                 int cur_input_row,
                 int cur_input_col,
                 double node_num,
                 double pool_row,
                 double pool_col,
                 double stride_row,
                 double stride_col,
                 std::string padding,
                 std::string name) {
    m_pool_row = pool_row;
    m_pool_col = pool_col;
    m_padding = padding;
    m_name = name;
    m_type = Layer::Pooling;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = m_in_size;
    m_output_row = m_row / m_pool_row;
    m_output_col = m_col / m_pool_col;
}

void
MaxPooling::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    for (int image = 0; image < m_in_size; ++image) {
        Eigen::MatrixXd pool_result((m_row / m_pool_row), (m_col / m_pool_col));
        for (int row = 0; row < m_row; row += m_pool_row) {
            for (int col = 0; col < m_col; col += m_pool_col) {
                pool_result((row / m_pool_row), (col / m_pool_col)) = m_input[image].block(row, col, m_pool_row, m_pool_col).maxCoeff();
            }
        }
        m_output.push_back(pool_result);
    }
}

#endif // CS133_LAYER_MAXPOOLING_IMPL_HPP