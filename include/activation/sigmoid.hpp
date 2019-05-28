// Implementation of the
// Sigmoid activation function


Sigmoid::Sigmoid(){
	// Not sure what to implement
}

Sigmoid::~Sigmoid(){}

void
Sigmoid::init() {
    m_type = Layer::Sigmoid;
}

void
Sigmoid::forward(std::vector<Eigen::MatrixXd> input){
    m_in_size = input.size();
    m_input = input;

    for (int i = 0; i < m_in_size; ++i) {
        m_output.push_back(1 / (1 + (-input[i].array()).exp()));
    }
    m_out_size = m_output.size();
}