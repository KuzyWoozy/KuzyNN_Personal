
void KuzyNN::activation::Activation::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = apply_forward(z_vector.index<double>(index));
    }
}

void KuzyNN::activation::Activation::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = apply_backward(z_vector.index<double>(index));
    }
}


/*
Relu
*/
double KuzyNN::activation::Relu::apply_forward(const double& z) const {
    return (z>0) ? z: 0;
}

double KuzyNN::activation::Relu::apply_backward(const double& z) const {
    return (z>0) ? 1 : 0;
}

KuzyNN::activation::Relu& KuzyNN::activation::Relu::clone() const {
    return *(new KuzyNN::activation::Relu {*this});
}

/*
LeakyRelu
*/
KuzyNN::activation::LeakyRelu::LeakyRelu(const double& leaky_num) : leaky_num {leaky_num} {}

double KuzyNN::activation::LeakyRelu::apply_forward(const double& z) const {
    return (z>0) ? z: z*leaky_num;
}

double KuzyNN::activation::LeakyRelu::apply_backward(const double& z) const {
    return (z>0) ? 1 : 0.01;
}

KuzyNN::activation::LeakyRelu& KuzyNN::activation::LeakyRelu::clone() const {
    return *(new KuzyNN::activation::LeakyRelu {*this});
}


/*
Tanh
*/
double KuzyNN::activation::TanH::apply_forward(const double& z) const {
    double denominator {(std::exp(z) + std::exp(z))};
    assert((denominator!=0) && "TanH forward, division by zero!");
    return (std::exp(z) - std::exp(-z)) / denominator; 
}

double KuzyNN::activation::TanH::apply_backward(const double& z) const {
    return 1-std::pow(KuzyNN::activation::TanH::apply_forward(z), 2);
}

KuzyNN::activation::TanH& KuzyNN::activation::TanH::clone() const {
    return *(new KuzyNN::activation::TanH {*this});
}


/*
Sigmoid
*/
double KuzyNN::activation::Sigmoid::apply_forward(const double& z) const {
    double denominator {(1+std::exp(-z))};
    assert((denominator!=0) && "Sigmoid forward, division by zero");
    return 1/denominator;
}

double KuzyNN::activation::Sigmoid::apply_backward(const double& z) const {
    return KuzyNN::activation::Sigmoid::apply_forward(z)*(1-KuzyNN::activation::Sigmoid::apply_forward(z));
}

KuzyNN::activation::Sigmoid& KuzyNN::activation::Sigmoid::clone() const {
    return *(new KuzyNN::activation::Sigmoid {*this});
}




