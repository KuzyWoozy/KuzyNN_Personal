
extern std::mt19937 seed;

KuzyMatrix::Matrix<double> KuzyNN::regularization::Dropout(const int& layerSize, const float& dropout_chance) {
    assert((layerSize>0) && ((dropout_chance >= 0) && (dropout_chance <= 1))  && "Error in Dropout function!");

    const KuzyMatrix::Matrix<double> dropout_mask_vector {{layerSize}};
    
    std::binomial_distribution<int> binomialDist {1, dropout_chance};

    for (int index{0}; index<dropout_mask_vector.get_shape()[0]; ++index) {
        dropout_mask_vector.index<double>(index) = static_cast<double>(binomialDist(seed));
    }

    return dropout_mask_vector;
}
