#ifndef CS133_LAYER_CONVOLUTIONAL_IMPL_HPP
#define CS133_LAYER_CONVOLUTIONAL_IMPL_HPP

// default constructor
Convolutional::Convolutional() {}

// default destructor
Convolutional::~Convolutional() {}

void
Convolutional::init(double row,
                    double col,
                    double node_num,
                    double kernal_row,
                    double kernal_col,
                    std::string padding,
                    std::string name) {
    m_row = row;
    m_col = col;
    m_node_num = node_num;
    m_kernal_row = kernal_row;
    m_kernal_col = kernal_col;
    m_padding = padding;
    m_name = name;
    m_type = Conv;
}

void
Convolutional::init(std::vector<std::vector<Eigen::MartixXd>> kernal) {
    m_kernal = kernal;
}

void
Convolutional::forward(std::vector<Eigen::MatrixXd> input, std::vector<double> weight, MatrixXd bias) {
    // how many pictures being input
    m_in_size = input.size();
    // deal with the input (need padding or not)
    if ( m_padding = "valid" ) {
        for (int i = 0; i < m_in_size; ++i) {
            MatrixXd image = Eigen::MatrixXd::Zero(m_row + 4, m_col + 4);
            image.block<m_row, m_col>(2, 2) += input[i];
            m_input.push_back(image);
        }
    }
    else if ( m_padding = "same" ) {
        m_input = input;
    }

    // compute the convolution
    for (int node = 0; node < m_node_num; ++node) {
        MatrixXd node_output(m_row - m_kernal_row + 1, m_col - m_kernal_col + 1);
        for (int image = 0; image < m_in_size; ++image) {
            MatrixXd cov_result(m_row - m_kernal_row + 1, m_col - m_kernal_col + 1);
            for (int row = 0; row < m_row - m_kernal_row + 1; ++row) {
                for (int col = 0; col < m_col - m_kernal_col + 1; ++col) {
                    double accumulation = 0;
                    for (int i = 0; i < m_kernal_row; ++i) {
                        for (int j = 0; j < m_kernal_col; ++j) {
                            accumulation += kernal[node][image](i, j) * m_input[image](row + i, col + j);
                        }
                    }
                    cov_result(row, col) = accumulation;
                }
            }
            node_output += weight[image] * cov_result;
        }
        node_output += bias;
        m_output.push_back(node_output);
    }

    m_out_size = m_output.size();
}

#endif // CS133_LAYER_CONVOLUTIONAL_IMPL_HPP