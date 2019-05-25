// TO-DO
// The identity activation function
// a child class of layer
#ifndef CS133_IDENTITY_HPP
#define CS133_IDENTITY_HPP

#include "Layer.hpp"

class Identity : public Layer{
public:
	Identity();
	~Identity();
	void init(Eigen::MatrixXd input_matrix);
	void forward();

private:
	size_t node_num;

	Eigen::MatrixXd input;

	Eigen::MatrixXd output;

	const int in_size;
	
	const int out_size;
};

#include "identity.hpp"

#endif // CS133_IDENTITY_HPP