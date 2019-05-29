// Implementation of the
// Sigmoid activation function


Sigmoid::Sigmoid(){
	// Not sure what to implement
}

Sigmoid::~Sigmoid(){}

void
Sigmoid::init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name) {
    m_type = Layer::Sigmoid;
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