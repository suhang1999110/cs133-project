#ifndef CS133_LAYER_DENSE_HPP
#define CS133_LAYER_DENSE_HPP

#include <Eigen/Core>
#include <vector>

template <typename Activation>
class Dense : class Layer{
 public:
  Dense();
  ~Dense();
  void init();
  void forward();
  
 private:
  size_t node_num;
};

#endif