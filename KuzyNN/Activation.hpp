#include <math.h>

/*
Relu
*/
void KuzyNN::activation::Relu::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = (z_vector.index<double>(index)>0) ? z_vector.index<double>(index) : 0;
    }
}

void KuzyNN::activation::Relu::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = (z_vector.index<double>(index)>0) ? 1 : 0;
    }
}

KuzyNN::activation::Relu& KuzyNN::activation::Relu::clone() const {
    return *(new KuzyNN::activation::Relu {*this});
}

/*
LeakyRelu
*/
KuzyNN::activation::LeakyRelu::LeakyRelu(const double& leaky_num) : leaky_num {leaky_num} {}

void KuzyNN::activation::LeakyRelu::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = (z_vector.index<double>(index)>=0) ? z_vector.index<double>(index): z_vector.index<double>(index)*leaky_num;
    }
}

void KuzyNN::activation::LeakyRelu::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
	if (z_vector.index<double>(index)>0) {
	    z_vector.index<double>(index) = 1; 
	}
	else if (z_vector.index<double>(index)==0) {
            z_vector.index<double>(index) = 0;
	}
	else {
	    z_vector.index<double>(index) = leaky_num; 
	}
    }
}

KuzyNN::activation::LeakyRelu& KuzyNN::activation::LeakyRelu::clone() const {
    return *(new KuzyNN::activation::LeakyRelu {*this});
}


/*
Tanh
*/
void KuzyNN::activation::TanH::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    double denominator;
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        denominator = (std::exp(z_vector.index<double>(index)) + std::exp(-z_vector.index<double>(index)));
        assert((denominator!=0) && "TanH forward, division by zero!");
        z_vector.index<double>(index) = (std::exp(z_vector.index<double>(index)) - std::exp(-(z_vector.index<double>(index)))) / denominator; 
    }
}

void KuzyNN::activation::TanH::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    KuzyNN::activation::TanH::forward(z_vector);
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = 1-std::pow(z_vector.index<double>(index), 2);
    }
}

KuzyNN::activation::TanH& KuzyNN::activation::TanH::clone() const {
    return *(new KuzyNN::activation::TanH {*this});
}

/*
Sigmoid
*/
void KuzyNN::activation::Sigmoid::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    double denominator;
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        denominator = 1+std::exp(-z_vector.index<double>(index));
        assert((denominator!=0) && "Sigmoid forward, division by zero");
        z_vector.index<double>(index) = 1/denominator; 
    }
}

void KuzyNN::activation::Sigmoid::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    KuzyNN::activation::Sigmoid::forward(z_vector);
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = z_vector.index<double>(index)*(1-z_vector.index<double>(index));
    }
}

KuzyNN::activation::Sigmoid& KuzyNN::activation::Sigmoid::clone() const {
    return *(new KuzyNN::activation::Sigmoid {*this});
}

/*
Softmax
*/
void KuzyNN::activation::Softmax::forward(const KuzyMatrix::Matrix<double>& z_vector) const {
    double max {z_vector.max()};

    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = std::exp(z_vector.index<double>(index)-max);
    }
    double sum {z_vector.sum()};
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = z_vector.index<double>(index)/sum;    
    }
}

void KuzyNN::activation::Softmax::backward(const KuzyMatrix::Matrix<double>& z_vector) const {
    double sum {0};
    double max {z_vector.max()};
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        sum += std::exp(z_vector.index<double>(index)-max);
    } 
    for (int index{0}; index<z_vector.get_shape()[0]; ++index) {
        z_vector.index<double>(index) = ((sum*std::exp(z_vector.index<double>(index)-max))-std::exp(2*(z_vector.index<double>(index)-max)))/std::pow(sum, 2); 
    }
}

KuzyNN::activation::Softmax& KuzyNN::activation::Softmax::clone() const {
    return *(new KuzyNN::activation::Softmax {*this});
}


