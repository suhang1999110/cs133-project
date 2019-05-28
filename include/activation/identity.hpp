// Implementation of the
// Identity activation function


Identity::Identity() {}

Identity::~Identity() {}

void
Identity::init() {
    m_type = Layer::Identity;
}

void
Identity::forward(std::vector<Eigen::MatrixXd> input) {
    m_in_size = m_input.size();
    m_input = input;
    m_out_size = m_in_size;
    m_output = m_input;
}