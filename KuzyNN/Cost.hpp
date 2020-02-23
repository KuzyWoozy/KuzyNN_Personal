#include <math.h>

extern const int logClip;

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


double KuzyNN::cost::Log::apply_forward(const double& output, const double& predict) const {
    if (predict == 0) {
        return -std::log(1-output);
    }
    else {
        return -std::log(output);
    }
}

double KuzyNN::cost::Log::apply_backward(const double& output, const double& predict) const {
    if (predict == 0) {
        if (output == 0) {
            return 0;
        }
        else if (output == 1) {
            return logClip;
        }
        else {
            return 1/(1-output);
        }
    }
    else {
        if (output == 0) {
            return -logClip;
        }
        else if (output == 1) {
            return 0;
        }
        else {
            return -1/output;
        }
    }
}

KuzyNN::cost::MSE& KuzyNN::cost::MSE::clone() const {
    return *(new KuzyNN::cost::MSE{*this});
}

KuzyNN::cost::Log& KuzyNN::cost::Log::clone() const {
    return *(new KuzyNN::cost::Log(*this));
}
