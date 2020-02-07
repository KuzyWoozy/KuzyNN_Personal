
extern std::mt19937 seed;
#include "math.h"


KuzyNN::initializer::Normal& KuzyNN::initializer::Normal::init(const int& numberOfParam) const {    
    return *(new KuzyNN::initializer::Normal {numberOfParam});
}

void KuzyNN::initializer::Normal::initialize(const KuzyMatrix::Matrix<double>& mat2transform) const {
    std::normal_distribution<double> normDist {0, 1/static_cast<double>(numberOfParam)};

    std::vector<double*> matPointers {mat2transform.flatten_pointers()};
    for (int index{0}; index<static_cast<int>(matPointers.size()); ++index) {
        (*matPointers[index]) = normDist(seed);
    }

}


