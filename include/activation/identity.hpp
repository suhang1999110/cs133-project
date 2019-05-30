///@file identity.hpp
///@brief Implementation of the Identity activation function

/// Constructor
Identity::Identity() {}

/// Destructor
Identity::~Identity() {}

/// Initialize the class
void
Identity::init( int cur_in_size,
                int cur_input_row,
                int cur_input_col,
                int node_num,
                int kernel_row,
                int kernel_col,
                int stride_row,
                int stride_col,
                std::string padding,
                std::string name) {
    m_type = Layer::Identity;
}

/// Spread foward to generate the response
void
Identity::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = m_input.size();
    m_input = input;
    m_out_size = m_in_size;
    m_output = m_input;
}