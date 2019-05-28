// Implementation of the
// ReLU activation function


Relu::Relu() {}

Relu::~Relu() {}

void
Relu::init() {
    m_type = Layer::ReLU;
}

void
Eigen::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = m_input.size();
    m_input = input;

    for(int i = 0; i < m_in_size; ++i) {
        m_output.push_back(input[i].cwiseMax(0));
    }
    m_out_size = m_output.size();
}