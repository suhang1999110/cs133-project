#ifndef CS133_LAYER_FLATTEN_HPP
#define CS133_LAYER_FLATTEN_HPP

class Flatten : public Layer {
public:
    Flatten();
    ~Flatten();
    void init(std::string name);
    void forward(std::vector<Eigen::MatrixXd> input);

private:
    // the row number of the input matrix
    int m_row;
    // the col number of the input matrix
    int m_col;
};

#endif