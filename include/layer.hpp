#ifndef CS133_LAYER_IMPL_HPP
#define CS133_LAYER_IMPL_HPP


Layer::Layer() {}

Layer::~Layer() {}

int
Layer::node_num() const {
    return m_node_num;
}

// get the row number of the input matrix
int
Layer::input_row() const {
    return m_row;
}

// get the col number of the input matrix
int
Layer::input_col() const {
    return m_col;
}

// get the row number of the output matrix
int
Layer::output_row() const {
    return m_output_row;
}
    
// get the col number of the output matrix
int
Layer::output_col() const {
    return m_output_col;
}

std::vector<Eigen::MatrixXd>
Layer::input() const {
    return m_input;
}

std::vector<Eigen::MatrixXd>
Layer::output() const {
    return m_output;
}

Layer::layerType
Layer::get_type() const {
    return m_type;
}

std::string
Layer::get_name() const {
    return m_name;
}

int
Layer::in_size() const {
    return m_in_size;
}

int
Layer::out_size() const {
    return m_out_size;
}

#endif // CS133_LAYER_IMPL_HPP