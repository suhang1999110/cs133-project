// Implementation of the
// ReLU activation function


Relu::Relu() {}

Relu::~Relu() {}

void
Relu::init( int cur_in_size,
            int cur_input_row,
            int cur_input_col,
            double node_num,
            double kernel_row,
            double kernel_col,
            double stride_row,
            double stride_col,
            std::string padding,
            std::string name) {
    m_type = Layer::ReLU;
}

void
Relu::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = m_input.size();
    m_input = input;

    for(int i = 0; i < m_in_size; ++i) {
        m_output.push_back(input[i].cwiseMax(0));
    }
    m_out_size = m_output.size();
}