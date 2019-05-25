// Implementation of the
// Identity activation function


Identity::Identity(){}

Identity::~Identity(){}

void Identity::init(Eigen::Matrix input_matrix){
	input = input_matrix;
	in_size = input.size();
}

void Identity::forward(){
	output = input;
	out_size = in_size;
}