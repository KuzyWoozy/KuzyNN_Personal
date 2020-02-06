
KuzyMatrix::Matrix<double> KuzyNN::cost::Cost::predict(const KuzyMatrix::Matrix<double>& output_vector, const KuzyMatrix::Matrix<double>& prediction_vector) const {
    assert((prediction_vector.get_shape() == output_vector.get_shape()) && "Prediction shape incompatible with network output shape");
    const KuzyMatrix::Matrix<double> vec2return_vector {output_vector.get_shape()};
    for (int index{0}; index<output_vector.get_shape()[0]; ++index) {
        vec2return_vector.index<double>(index) = apply_forward(output_vector.index<double>(index), prediction_vector.index<double>(index));
    }
    return vec2return_vector;
}

KuzyMatrix::Matrix<double> KuzyNN::cost::Cost::error(const KuzyMatrix::Matrix<double>& output_vector, const KuzyMatrix::Matrix<double>& prediction_vector) const {
    assert((prediction_vector.get_shape() == output_vector.get_shape()) && "Prediction shape incompatible with network output shape");
    const KuzyMatrix::Matrix<double> vec2return_vector {output_vector.get_shape()};
    for (int index{0}; index<output_vector.get_shape()[0]; ++index) {
        vec2return_vector.index<double>(index) = apply_backward(output_vector.index<double>(index), prediction_vector.index<double>(index));
    }
    return vec2return_vector;
}

double KuzyNN::cost::MSE::apply_forward(const double& output, const double& predict) const {
    return std::pow((output - predict), 2);
}

double KuzyNN::cost::MSE::apply_backward(const double& output, const double& predict) const {
    return 2 * (output - predict);
}

KuzyNN::cost::MSE& KuzyNN::cost::MSE::clone() const {
    return *(new KuzyNN::cost::MSE{*this});
}
