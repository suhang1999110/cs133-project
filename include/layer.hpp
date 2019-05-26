#ifndef CS133_LAYER_IMPL_HPP
#define CS133_LAYER_IMPL_HPP


Layer::Layer() {}

Layer::~Layer() {}

Layer::layerType
Layer::get_type() const {
    return m_type;
}

std::string
Layer::get_name() const {
    return m_name;
}

Eigen::MatrixXd
Layer::output() const {
    return m_output;
}

size_t
Layer::num_node() const {
  return m_node_num;
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