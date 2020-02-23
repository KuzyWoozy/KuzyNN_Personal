#include "KuzyMatrix.h"
#include <vector>
#include <iostream>

int main() {
    

    KuzyMatrix::Matrix<double> x ({3});
    x.fill(3);
    std::cout << x.max() << '\n';
    return 0;
}
