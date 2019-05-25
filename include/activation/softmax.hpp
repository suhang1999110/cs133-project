// Implementation of the
// Softmax activation funxtion

Softmax::Softmax(){
	// Not sure what to implement
}

Softmax::~Softmax(){}

void Softmax::init(Eigen::MatrixXd input_matrix){
	input = input_matrix;
	in_size = input.size();
}

void Softmax::forward(){
	Eigen::MatrixXd result = input;
	double exp_sum = 0;
	int col = input.cols();
	int row = input.rows();
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			result(j, i) = exp(result(j, i));
			exp_sum += result(j, i);
		}
	}
	for (int i = 0; i < col; ++i) {
		for (int j = 0; j < row; ++j) {
			result(j, i) = result(j, i) / exp_sum;
		}
	}
	output = result;
	out_size = output.size();
}