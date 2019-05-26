// TO-DO
// The Softmax activation function
// a child class of layer
#ifndef CS133_SOFTMAX_HPP
#define CS133_SOFTMAX_HPP

#include "Layer.hpp"

class Softmax : public Layer {
public:
	Softmax();
	~Softmax();
	void init();
	void forward();
};

#include "softmax.hpp"

#endif // CS133_SOFTMAX_HPP