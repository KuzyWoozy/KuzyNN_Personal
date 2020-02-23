
extern std::mt19937 seed;
#include "math.h"


KuzyNN::initializer::Normal& KuzyNN::initializer::Normal::init(const int& numberOfParam) const {    
    return *(new KuzyNN::initializer::Normal {numberOfParam});
}

KuzyNN::initializer::Uniform& KuzyNN::initializer::Uniform::init(const int& numberOfParam) const {
    return *(new KuzyNN::initializer::Uniform {});
}

KuzyNN::initializer::Static& KuzyNN::initializer::Static::init(const int& numberOfParam) const {
    return *(new KuzyNN::initializer::Static {numberOfParam});
}

void KuzyNN::initializer::Normal::initialize(const KuzyMatrix::Matrix<double>& mat2transform) const {
    std::normal_distribution<double> normDist (0, 1/static_cast<double>(numberOfParam));
    std::vector<double*> matPointers {mat2transform.flatten_pointers()};
    for (int index{0}; index<static_cast<int>(matPointers.size()); ++index) {
        (*matPointers[index]) = normDist(seed);
    }
}

void KuzyNN::initializer::Uniform::initialize(const KuzyMatrix::Matrix<double>& mat2transform) const {
    std::uniform_real_distribution<double> uniDist (-1,1);

    std::vector<double*> matPointers {mat2transform.flatten_pointers()};
    for (int index{0}; index<static_cast<int>(matPointers.size()); ++index) {
        (*matPointers[index]) = uniDist(seed);
    } 
}

void KuzyNN::initializer::Static::initialize(const KuzyMatrix::Matrix<double>& mat2transform) const {
    double val = 1/numberOfParam;
    std::vector<double*> matPointers {mat2transform.flatten_pointers()};
    for (int index{0}; index<static_cast<int>(matPointers.size()); ++index) {
        (*matPointers[index]) = val;
    }
}






