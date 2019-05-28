///
///@file this file implement the identity activation function
#ifndef CS133_IDENTITY_HPP
#define CS133_IDENTITY_HPP

#include "Layer.hpp"

/// @brief identity activation function
///
/// As child class of layer
class Identity : public Layer {
public:
	Identity();  ///< Default constructor
	~Identity();   ///< Destructor
	void init();   ///< Function of initialize the class
	void forward();   ///< forward spread of the nework
};

#include "identity.hpp"

#endif // CS133_IDENTITY_HPP