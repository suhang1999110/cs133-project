#ifndef CS133_LAYER_IMPL_HPP
#define CS133_LAYER_IMPL_HPP


Layer::Layer() {}

Layer::~Layer() {}

int
Layer::node_num() const {
    return m_node_num;
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

size_t
Layer::in_size() const {
    return m_in_size;
}

size_t
Layer::out_size() const {
    return m_out_size;
}

#endif // CS133_LAYER_IMPL_HPP