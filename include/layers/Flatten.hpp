#ifndef CS133_LAYER_FLATTEN_HPP
#define CS133_LAYER_FLATTEN_HPP

class Flatten : public Layer {
public:
    Flatten();
    ~Flatten();
    void init(std::string name);
    void forward(std::vector<Eigen::MatrixXd> input);
private:
    std::vector<double> m_output;
};

#endif