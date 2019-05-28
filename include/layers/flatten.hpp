#ifndef CS133_LAYER_FLATTEN_IMPL_HPP
#define CS133_LAYER_FLATTEN_IMPL_HPP

Flatten::Flatten() {}

Flatten::~Flatten() {}

void
Flatten::init(std::string name) {
    m_name = name;
    m_type = Flatten;
}

void
Flatten::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = input.size();
    m_input = input;
    m_row = m_input[0].rows();
    m_col = m_input[0].cols();

    for (int image = 0; image < m_in_size; ++image) {
        for (int row = 0; row < m_row; ++row) {
            for (int col = 0; col < m_col; ++col) {
                m_output.push_back(m_input[image](row, col));
            }
        }
    }
    m_out_size = 1;
}

#endif // CS133_LAYER_FLATTEN_IMPL_HPP