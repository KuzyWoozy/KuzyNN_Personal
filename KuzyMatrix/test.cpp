#include "KuzyMatrix.h"

int main() {
    

    KuzyMatrix::Matrix<double> x ({10, 10, 10});
    x.fill(10);

    (x / 2).print();
    return 0;
}
