///@file Node.hpp
///@brief Class of Node
#ifndef CS133_NODE_HPP
#define CS133_NODE_HPP

#include <Eigen/Core>

///@brief Node Class
///
/// The basic computing unit
class Node{
 public:

  Node();   ///<donstructor
 
  ~Node();  ///<destructor
  
 private:
  Eigen::VectorXd node;  ///< A dynamic matrix to represent the node
}

#endif // CS133_NODE_HPP
