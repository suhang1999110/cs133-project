// Implementation of the
// Sigmoid activation function


Sigmoid::Sigmoid() {}

Sigmoid::~Sigmoid() {}

void
Sigmoid::init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              int node_num,
              int kernel_row,
              int kernel_col,
              int stride_row,
              int stride_col,
              std::string padding,
              std::string name) {
    m_type = Layer::Sigmoid;
    m_name = name;
}

void
Sigmoid::forward(std::vector<Eigen::MatrixXd> input){
    m_in_size = input.size();
    m_input = input;

    for (int i = 0; i < m_in_size; ++i) {
        m_output.push_back(1 / (1 + (-input[i].array()).exp()));
    }
    m_out_size = m_output.size();
}