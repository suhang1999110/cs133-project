// Implementation of the
// ReLU activation function


Relu::Relu(){
	/// Not sure what to implement
}

Relu::~Relu(){}

void Relu::init(Eigen::MatrixXd input_matrix){
	input = input_matrix;
	in_size = input.size();
}

void Eigen::forward(){
	Eigen::MatrixXd result = input;
	int col = input.cols();
	int row = input.rows();
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			result(j, i) = std::max(0, result(j, i));
		}
	}
	output = result;
}