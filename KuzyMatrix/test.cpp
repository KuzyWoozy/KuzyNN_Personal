#include "KuzyMatrix.h"

int main() {
    

    KuzyMatrix::Matrix<double> x ({1});
    x.fill(-10);
    KuzyMatrix::Matrix<double> y ({1});
    y.fill(2);
    y.subtract(x);
    y.print();
    return 0;
}
