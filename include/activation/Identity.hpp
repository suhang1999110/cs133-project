// TO-DO
// The identity activation function
// a child class of layer
#ifndef CS133_IDENTITY_HPP
#define CS133_IDENTITY_HPP

#include "Layer.hpp"

class Identity : public Layer {
public:
	Identity();
	~Identity();
	void init();
	void forward();
};

#include "identity.hpp"

#endif // CS133_IDENTITY_HPP