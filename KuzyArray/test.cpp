#include <iostream>

#include "KuzyArray.h"


int main() {

    KuzyArray::Matrix<int> x {3, 3};
    x.fill(14);
    KuzyArray::Matrix<int> y {3, 3};
    y.fill(7);

    (x / y).print();


    return 0;
}
