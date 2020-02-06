#include <iostream>
#include "frac.h"

int main() {
    std::cout << "Enter numinator: ";
    int sub {userInput()};
    std::cout << "Enter a denominator";
    int dom {userInput()};

    Fraction* frac = new Fraction(sub, dom);

    (*frac).print();

    return 0;
}
