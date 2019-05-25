#ifndef CS133_LAYER_IMPL_HPP
#define CS133_LAYER_IMPL_HPP

#include "Layer.hpp"

Layer::Layer(const int in_size, const int out_size):m_in_size(in_size), m_out_size(out_size){}

size_t
Layer::num_node() const{
  return m_node_num;
}

size_t
Layer::in_size() const{
  return m_in_size;
}

size_t
Layer::out_size() const{
  return m_out_size;
}

#endif // CS133_LAYER_IMPL_HPP