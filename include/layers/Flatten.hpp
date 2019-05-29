///@file Flatten.hpp
///@brief A layer to process the input data
///
/// This kind of layer is used to decrease the dimension
/// of the input data, transfer the input data to a single 
/// column vector

#ifndef CS133_LAYER_FLATTEN_HPP
#define CS133_LAYER_FLATTEN_HPP

#include "../Layer.hpp"

///@brief The class of dense layer
///
/// This kind of layer is used to decrease the dimension
/// of the input data, transfer the input data to a single 
/// column vector
class Flatten : public Layer {
public:
    Flatten();   ///< Constructor
    ~Flatten();  ///< Destructor
    void init(int cur_in_size,
              int cur_input_row,
              int cur_input_col,
              double node_num,
              double kernel_row,
              double kernel_col,
              double stride_row,
              double stride_col,
              std::string padding,
              std::string name);  ///< Initialize the layer with those arguments
    void forward(std::vector<Eigen::MatrixXd> input);  ///< Spread forward and get the response
};

#include "flatten.hpp"

#endif