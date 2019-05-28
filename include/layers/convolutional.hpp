#ifndef CS133_LAYER_CONVOLUTIONAL_IMPL_HPP
#define CS133_LAYER_CONVOLUTIONAL_IMPL_HPP

// default constructor
Convolutional::Convolutional() {}

// default destructor
Convolutional::~Convolutional() {}

void
Convolutional::init(double node_num,
                    double kernel_row,
                    double kernel_col,
                    double stride_row,
                    double stride_col,
                    std::string padding,
                    std::string name) {
    m_node_num = node_num;
    m_kernel_row = kernel_row;
    m_kernel_col = kernel_col;
    m_stride_row = stride_row;
    m_stride_col = stride_col;
    m_padding = padding;
    m_name = name;
    m_type = Conv;
}

void
Convolutional::init(std::vector<std::vector<Eigen::MartixXd>> kernel,
                    std::vector<double> weight,
                    Eigen::MatrixXd bias) {
    m_kernel = kernel;
    m_weight = weight;
    m_bias = bias;
}

void
Convolutional::forward(std::vector<Eigen::MatrixXd> input) {
    // how many pictures being input
    m_in_size = input.size();
    // deal with the input (need padding or not)
    if ( m_padding = "valid" ) {
        for (int i = 0; i < m_in_size; ++i) {
            Eigen::MatrixXd image = Eigen::MatrixXd::Zero(m_row + 4, m_col + 4);
            image.block<m_row, m_col>(2, 2) += input[i];
            m_input.push_back(image);
        }
    }
    else if ( m_padding = "same" ) {
        m_input = input;
    }
    m_row = m_input[0].rows();
    m_col = m_input[0].cols();

    // compute the convolution
    for (int node = 0; node < m_node_num; ++node) {
        Eigen::MatrixXd node_output(m_row - m_kernel_row + 1, m_col - m_kernel_col + 1);
        for (int image = 0; image < m_in_size; ++image) {
            Eigen::MatrixXd cov_result(m_row - m_kernel_row + 1, m_col - m_kernel_col + 1);
            for (int row = 0; row < m_row - m_kernel_row + 1; row += m_stride_row) {
                for (int col = 0; col < m_col - m_kernel_col + 1; col += m_stride_col) {
                    double accumulation = 0;
                    for (int i = 0; i < m_kernel_row; ++i) {
                        for (int j = 0; j < m_kernel_col; ++j) {
                            accumulation += m_kernel[node][image](i, j) * m_input[image](row + i, col + j);
                        }
                    }
                    cov_result(row, col) = accumulation;
                }
            }
            node_output += m_weight[image] * cov_result;
        }
        node_output += m_bias;
        m_output.push_back(node_output);
    }

    m_out_size = m_output.size();
}

#endif // CS133_LAYER_CONVOLUTIONAL_IMPL_HPP