// Implementation of the
// Sigmoid activation function


Sigmoid::Sigmoid(){
	// Not sure what to implement
}

Sigmoid::~Sigmoid(){}

void Sigmoid::init(Eigen::MatrixXd input_matrix){
	input = input_matrix;
	in_size = input.size();
}

void Sigmoid::forward(){
	Eigen::MatrixXd result = input;
	int col = input.cols();
	int row = input.rows();
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			result(j, i) = 1 / (1 + exp(-result(j, i)));
		}
	}
	output = result;
	out_size = output.size();
}