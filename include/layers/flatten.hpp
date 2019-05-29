#ifndef CS133_LAYER_FLATTEN_IMPL_HPP
#define CS133_LAYER_FLATTEN_IMPL_HPP

Flatten::Flatten() {}

Flatten::~Flatten() {}

void
Flatten::init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name) {
    m_name = name;
    m_type = Layer::Flatten;
    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = 1;
    m_output_row = m_in_size * m_row * m_col;
    m_output_col = 1;
}

void
Flatten::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    Eigen::MatrixXd flatten_result((m_in_size * m_row * m_col) , 1);
    for (int image = 0; image < m_in_size; ++image) {
        for (int row = 0; row < m_row; ++row) {
            for (int col = 0; col < m_col; ++col) {
                flatten_result((image * m_row * m_col + row * m_col + col), 1) = m_input[image](row, col);
            }
        }
    }
    m_output.push_back(flatten_result);
}

#endif // CS133_LAYER_FLATTEN_IMPL_HPP