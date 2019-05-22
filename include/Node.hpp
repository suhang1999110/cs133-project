#ifndef CS133_NODE_HPP
#define CS133_NODE_HPP

#include <Eigen/Core>

class Node{
 public:
  Node();
  ~Node();
 private:
  Eigen::VectorXd node;   
}

#endif // CS133_NODE_HPP
