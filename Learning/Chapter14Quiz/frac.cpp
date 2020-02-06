#include "frac.h"
#include <cassert>
#include <iostream>

int userInput() {
    int x;
    std::cin >> x;
    return x;
}

Fraction::Fraction(int x, int y) {
    assert(y>0);
    sub = x;
    dom = y;
}

void Fraction::print() const {
    std::cout << sub << "/"<< dom << '\n';
}


