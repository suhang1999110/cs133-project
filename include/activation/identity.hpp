///@file identity.hpp
///@brief Implementation of the Identity activation function
#ifndef CS133_IDENTITY_IMPL_HPP
#define CS133_IDENTITY_IMPL_HPP

/// Constructor
Identity::Identity() {}

/// Destructor
Identity::~Identity() {}

/// Initialize the class
void
Identity::init(int cur_in_size,
               int cur_input_row,
               int cur_input_col,
               int non_arg1,
               int non_arg2,
               int non_arg3,
               int non_arg4,
               int non_arg5,
               std::string non_arg6,
               std::string name) {
    m_name = name;
    m_type = Layer::Identity;

    m_in_size = cur_in_size;
    m_row = cur_input_row;
    m_col = cur_input_col;
    m_out_size = m_in_size;
    m_output_row = m_row;
    m_output_col = m_col;
}

/// Spread foward to generate the response
void
Identity::forward(std::vector<Eigen::MatrixXd> input) {
    m_input = input;

    m_output = m_input;
}

#endif // CS133_IDENTITY_IMPL_HPP